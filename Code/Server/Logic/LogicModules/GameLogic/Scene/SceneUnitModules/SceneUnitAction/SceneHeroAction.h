#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Utils/Ticker.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"

class AISceneUnitHero;

namespace GameLogic
{
	class Skill;

	class SceneHeroAction : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE/* = ESceneUnitModule_Action*/;
	public:
		SceneHeroAction();
		virtual ~SceneHeroAction() override;

	protected:
		virtual void OnEnterScene() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	public:
		bool Trace(uint64_t suid, float allow_distance);
		bool MoveTo(Vector3 pos, float allow_distance);
		void CancelMove();
		bool UseSkill(int skill_id, uint64_t su_id, Vector2 pos, float dir);
		bool CancelSkill();

	protected:
		void ProcessMove();
		void ProcessUseSkill();

		ESUAction m_action = ESUAction_Idle;
		ESUAction m_next_action = ESUAction_Idle;

		struct MoveParam
		{
			void Reset()
			{
				target_suid = 0;
				target_su.reset();
				target_pos = Vector3::zero;
				allow_distance = 0;
				Ticker check_span;
				try_moving = false;
				first_check = true;
			}

			uint64_t target_suid = 0;
			std::shared_ptr<SceneUnit> target_su;
			Vector3 target_pos;
			float allow_distance = 0;
			Ticker check_span;
			bool try_moving = false;
			bool first_check = true;
		};
		MoveParam m_move_param;
		std::shared_ptr<Skill> m_using_skill = nullptr;

	protected:
		AISceneUnitHero *m_bt_agent;

	protected:
		virtual std::vector<SyncClientMsg> CollectPBInit() override;
	};
}

