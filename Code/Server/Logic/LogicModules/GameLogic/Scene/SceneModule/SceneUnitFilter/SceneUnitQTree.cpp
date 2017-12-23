#include "SceneUnitQTree.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{	
	void SceneUnitQTreeNodeUnit::Deattach()
	{
		for (SceneUnitQTreeNode *qtree_node : attached_qtree_nodes)
		{
			qtree_node->node_units.erase(this);
		}
		attached_qtree_nodes.clear();
	}

	void SceneUnitQTreeNodeUnit::Attach(SceneUnitQTreeNode * node)
	{
		node->node_units.insert(this);
		attached_qtree_nodes.insert(node);
	}

	SceneUnitQTreeNode * SceneUnitQTree::CreateNode(AABB2 rect, int layer, SceneUnitQTree *tree)
	{
		SceneUnitQTreeNode *node = new SceneUnitQTreeNode();
		node->area = rect;
		node->layer = layer;
		node->tree = tree;
		memset(node->children, 0, sizeof(node->children));
		return node;
	}

	void SceneUnitQTree::ReleaseNode(SceneUnitQTreeNode * root)
	{
		if (nullptr == root)
			return;

		std::vector<SceneUnitQTreeNode *> nodes;
		nodes.push_back(root);
		while (!nodes.empty())
		{
			SceneUnitQTreeNode *node = nodes.back();
			nodes.pop_back();

			for (int i = 0; i < SceneUnitQTreeNode::EChild_Count; ++i)
			{
				if (nullptr != node->children[i])
					nodes.push_back(node->children[i]);
			}
			for (SceneUnitQTreeNodeUnit *unit : node->node_units)
			{
				unit->Deattach();
			}
			
			delete node; node = nullptr;
		}
	}

	void SceneUnitQTree::Init(AABB2 map_rect)
	{
		this->Release();
		root = SceneUnitQTree::CreateNode(map_rect, 0, this);
	}

	void SceneUnitQTree::Release()
	{
		SceneUnitQTree::ReleaseNode(root);
		root = nullptr;
	}

	bool SceneUnitQTree::CanSplitBody(SceneUnitQTreeNode * node)
	{
		return node->layer <= max_split_body_layer;
	}

	bool SceneUnitQTree::CanOwnChildren(SceneUnitQTreeNode * node)
	{
		return node->layer < max_layer;
	}

	void SceneUnitQTree::FindUnits(const AABB2 & rect, std::unordered_set<SceneUnitQTreeNodeUnit*>& out_units)
	{
		if (nullptr == root)
			return;

		AABB2 cover_rect;
		bool ret = GeometryUtils::CalAABB2Intersect(root->area, rect, &cover_rect);
		if (!ret || cover_rect.IsEmpty())
			return;

		root->FindUnits(cover_rect, out_units);
	}

	void SceneUnitQTree::UpdateNodeUnit(SceneUnitQTreeNodeUnit * node_unit)
	{
		if (nullptr == node_unit)
			return;
		node_unit->Deattach();

		if (nullptr == root || nullptr == node_unit->unit)
			return;
		std::shared_ptr<SceneUnitBody> su_body = node_unit->unit->GetModule<SceneUnitBody>();
		if (nullptr == su_body)
			return;

		AABB2 cover_rect;
		bool ret = GeometryUtils::CalAABB2Intersect(root->area, su_body->CovertRect(), &cover_rect);
		if (ret)
			root->AddUnit(node_unit, cover_rect);
	}

	void SceneUnitQTreeNode::FindUnits(const AABB2 & rect, std::unordered_set<SceneUnitQTreeNodeUnit*>& out_units)
	{
		AABB2 cover_rect;
		bool ret = GeometryUtils::IsAABB2Intersect(this->area, rect);
		if (!ret)
			return;

		std::vector<SceneUnitQTreeNode *> nodes;
		nodes.push_back(this);

		while (!nodes.empty())
		{
			SceneUnitQTreeNode *node = nodes.back();
			nodes.pop_back();

			if (GeometryUtils::IsAABB2Intersect(node->area, rect))
			{
				out_units.insert(node->node_units.begin(), node->node_units.end());
				if (node->HasChildren())
				{
					for (int i = 0; i < SceneUnitQTreeNode::EChild_Count; ++i)
					{
						nodes.push_back(node->children[i]);
					}
				}
			}
		}
	}

	void SceneUnitQTreeNode::AddUnit(SceneUnitQTreeNodeUnit * unit, const AABB2 &cover_rect)
	{
		// this.area 必定是包含cover_rect
		if (!this->tree->CanOwnChildren(this))
		{
			// 叶子节点直接atttach
			unit->Attach(this);
			return;
		}

		if (!this->HasChildren())
		{
			if (this->node_units.size() < this->tree->split_capacity)
			{
				// 节点没有children且未达到分裂容量
				unit->Attach(this);
				return;
			}

			// 创建子节点
			Vector2 lt = this->area.lt;
			Vector2 rb = this->area.rb;
			float y_val = rb.y - lt.y;
			float x_val = rb.x - lt.x;
			{
				AABB2 child_area; 
				child_area.lt = this->area.lt; 
				child_area.rb = lt + Vector2(x_val/2, y_val/2);
				this->children[SceneUnitQTreeNode::EChild_LT] = SceneUnitQTree::CreateNode(child_area, this->layer + 1, this->tree);
			}
			{
				AABB2 child_area; 
				child_area.lt = lt + Vector2(x_val/2, y_val/2); 
				child_area.rb = this->area.rb;
				this->children[SceneUnitQTreeNode::EChild_RB] = SceneUnitQTree::CreateNode(child_area, this->layer + 1, this->tree);
			}
			{
				AABB2 child_area; 
				child_area.lt = lt + Vector2(x_val/2 , 0); 
				child_area.rb = lt + Vector2(x_val, y_val/2);
				this->children[SceneUnitQTreeNode::EChild_RT] = SceneUnitQTree::CreateNode(child_area, this->layer + 1, this->tree);
			}
			{
				AABB2 child_area; 
				child_area.lt = lt + Vector2(0, y_val/2); 
				child_area.rb = lt + Vector2(x_val/2, y_val);
				this->children[SceneUnitQTreeNode::EChild_LB] = SceneUnitQTree::CreateNode(child_area, this->layer + 1, this->tree);
			}
		}
		else
		{
			if (this->layer >= this->tree->max_layer - 2) 
			{
				// 倒数第二层的node若是子节点没有unit，且本node的unit数少于split_capacity/2,
				// 则删除子节点，把unit加到本node
				if (this->node_units.size() < this->tree->split_capacity * 0.5 && this->GetNodeUnitCount() <= this->node_units.size())
				{
					size_t node_units_num = this->GetNodeUnitCount();
					auto node_units_xx = this->GetNodeUnits();
					// unit数不足分裂数一半,且叶子节点没有unit
					for (int i = 0; i < SceneUnitQTreeNode::EChild_Count; ++i)
					{
						SceneUnitQTree::ReleaseNode(this->children[i]);
						this->children[i] = nullptr;
					}
					unit->Attach(this);
					return;
				}
			}
		}

		{
			int include_child = -1;
			for (int i = 0; i < SceneUnitQTreeNode::EChild_Count; ++i)
			{
				if (GeometryUtils::IsAABB2Include(this->children[i]->area, cover_rect))
				{
					include_child = i;
					break;
				}
			}
			if (include_child >= 0)
			{
				// 若某个子节点包含cover_rect则unit加入此子节点
				this->children[include_child]->AddUnit(unit, cover_rect);
				return;
			}
		}

		{
			if (!this->tree->CanSplitBody(this))
			{
				// 不存在子节点包含cover_rect，切该子节点不能分隔body
				unit->Attach(this);
				return;
			}
		}

		{
			// 切割cover_rect分别加入子节点
			for (int i = 0; i < SceneUnitQTreeNode::EChild_Count; ++i)
			{
				AABB2 rect_intersect;
				if (GeometryUtils::CalAABB2Intersect(this->children[i]->area, cover_rect, &rect_intersect))
				{
					this->children[i]->AddUnit(unit, rect_intersect);
				}
			}
		}
	}

	void SceneUnitQTreeNode::Travel(std::function<void(SceneUnitQTreeNode*)> func)
	{
		if (nullptr == func)
			return;

		std::vector<SceneUnitQTreeNode *> nodes;
		nodes.push_back(this);
		while (!nodes.empty())
		{
			SceneUnitQTreeNode *node = nodes.back();
			nodes.pop_back();
			if (node->HasChildren())
			{
				for (int i = 0; i < SceneUnitQTreeNode::EChild_Count; ++i)
				{
					nodes.push_back(node->children[i]);
				}
			}
			func(node);
		}
	}
	std::unordered_set<SceneUnitQTreeNodeUnit*> SceneUnitQTreeNode::GetNodeUnits()
	{
		std::unordered_set<SceneUnitQTreeNodeUnit*> ret;
		this->Travel([&ret](SceneUnitQTreeNode *node) {
			ret.insert(node->node_units.begin(), node->node_units.end());
		});
		return ret;
	}
	size_t SceneUnitQTreeNode::GetNodeUnitCount()
	{
		size_t ret = 0;
		this->Travel([&ret](SceneUnitQTreeNode *node) {
			ret += node->node_units.size();
		});
		return ret;
	}
}
