#pragma once
#include "Common/Geometry/GeometryDefine.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <array>

namespace GameLogic
{
	class SceneUnit;
	struct SceneUnitQTreeNode;
	struct SceneUnitQTree;

	struct SceneUnitQTreeNodeUnit
	{
		std::weak_ptr<SceneUnit> unit;
		std::unordered_set<SceneUnitQTreeNode *> attached_qtree_nodes;

		void Deattach();
		void Attach(SceneUnitQTreeNode *node);
	};

//	area.lt--------------
	//    |	 lt  |  rt  |
	//	  |------|------|
	//    |	 lb  |  rb  |
	//	  ---------------area.rb

	struct SceneUnitQTreeNode
	{
		enum EChild
		{
			EChild_LT = 0,
			EChild_RT,
			EChild_RB,
			EChild_LB,
			EChild_Count,
		};

		AABB2 area;
		int layer = 0;

		SceneUnitQTree *tree = nullptr;
		std::array<SceneUnitQTreeNode *, EChild_Count> children = { nullptr };
		// SceneUnitQTreeNode *children[EChild_Count] = { nullptr };
		std::unordered_set<SceneUnitQTreeNodeUnit *> node_units;

		void FindUnits(const AABB2 &rect, std::unordered_set<SceneUnitQTreeNodeUnit *> &out_units);
		void AddUnit(SceneUnitQTreeNodeUnit *unit, const AABB2 &cover_rect);
		bool HasChildren() { return nullptr != children[0]; }
		void Travel(std::function<void(SceneUnitQTreeNode *)> func);
		std::unordered_set<SceneUnitQTreeNodeUnit *> GetNodeUnits();
		size_t GetNodeUnitCount();
	};

	struct SceneUnitQTree
	{
		static const int DEFAULT_MAX_LAYER/* = 4*/;			// 0 - 4,����4
		static const size_t DEFAULT_SPLIT_CAPACITY/* = 4*/;	// �����ﵽ���������

		SceneUnitQTreeNode *root = nullptr;
		int max_layer = DEFAULT_MAX_LAYER;
		size_t split_capacity = DEFAULT_SPLIT_CAPACITY;
		int max_split_body_layer = 2;

		SceneUnitQTree() {}
		~SceneUnitQTree() { this->Release(); }

		static SceneUnitQTreeNode * CreateNode(AABB2 rect, int layer, SceneUnitQTree *tree);
		static void ReleaseNode(SceneUnitQTreeNode *root);

		void Init(AABB2 map_rect);
		void Release();
		void UpdateNodeUnit(SceneUnitQTreeNodeUnit *unit);
		bool CanSplitBody(SceneUnitQTreeNode *node);
		bool CanOwnChildren(SceneUnitQTreeNode *node);

		void FindUnits(const AABB2 &rect, std::unordered_set<SceneUnitQTreeNodeUnit *> &out_units);
	};
}