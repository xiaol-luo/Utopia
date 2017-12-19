#pragma once

#include "GameLogic/Scene/SceneModule/SceneModule.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Common/Geometry/GeometryDefine.h"

namespace GameLogic
{
	class SceneUnitFilter : public SceneModule
	{
	public:
		static const ESceneModule MODULE_TYPE = ESceneModule_UnitFilter;
	public:
		SceneUnitFilter();
		virtual ~SceneUnitFilter() override;

	public:
		std::unordered_set<std::shared_ptr<SceneUnit>> FilterSceneUnit(EffectFilterOption filter_option);

	protected:
		virtual bool OnAwake() override;
		virtual void OnUpdate() override;

		struct QTreeNode;
		struct UnitNode
		{
			UnitNode *pre = nullptr;
			UnitNode *next = nullptr;
			std::shared_ptr<SceneUnit> unit = nullptr;

			QTreeNode *qTreeNode = nullptr;
			void Deatach()
			{
				if (nullptr != qTreeNode)
				{
					--qTreeNode->unit_num;
					qTreeNode = nullptr;
				}
				if (nullptr != pre)
					pre->next = next;
				if (nullptr != next)
					next->pre = pre;
				pre = nullptr;
				next = nullptr;
			}
			void Attach(QTreeNode *node)
			{
				this->Deatach();
				this->qTreeNode = node;
				++node->unit_num;
				this->next = node->units.next;
				if (nullptr != node->units.next)
					node->units.next->pre = this;
				this->pre = &node->units;
				node->units.next = this;
			}
		};

		struct QTreeNode
		{
			static const int MAX_LAYER = 4;
			static const int SPLIT_CAPACITY = 4;	// 容量超过才允许分裂

			AABB2 rect;
			int layer = 0;
			QTreeNode *lt = nullptr;
			QTreeNode *rt = nullptr;
			QTreeNode *rb = nullptr;
			QTreeNode *lb = nullptr;
			
			int unit_num = 0;
			UnitNode units;
		};

		std::unordered_map<uint64_t, UnitNode *> m_id_unit_map;
		void OnSceneUnitEnterScene(std::shared_ptr<SceneUnit> su);
		void OnSceneUnitLeaveScene(std::shared_ptr<SceneUnit> su);
		void OnSceneUnitPosChange(std::shared_ptr<SceneUnit> su, Vector3 old_pos, Vector3 new_pos);
	};
}
