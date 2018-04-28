#pragma once

#include "GameLogic/Scene/Missile/SceneUnitMissile.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Common/Utils/Ticker.h"

namespace GameLogic
{
	class Skill;

	struct GuidedMissileParam
	{
		enum TargetType
		{
			TargetType_Pos,
			TargetType_SceneUnit,
		};

		TargetType target_type;
		Vector3 target_pos;
		std::shared_ptr<SceneUnit> target_su;
		float move_speed = 0;
		float max_alive_sec = 20.0f;
		UseEffectParam use_effect_param;
		std::vector<int> effect_ids;
	};

	enum GuidedMissileState
	{
		GuidedMissileState_None = 0,
		GuidedMissileState_Ready,
		GuidedMissileState_Moving,
		GuidedMissileState_Hit,
		GuidedMissileState_Done,
		GuidedMissileState_Destroy,
		GuidedMissileState_AllFinish,
	};

	class SceneUnitGuidedMissile : public SceneUnitMissile
	{
	public:
		SceneUnitGuidedMissile();
		virtual ~SceneUnitGuidedMissile() override;

		bool SetParam(const GuidedMissileParam &param);
		void virtual OnAwake() override;
		virtual void OnUpdate() override;

	protected:
		GuidedMissileParam m_param;
		std::shared_ptr<SceneUnitTransform> m_transform;
		GuidedMissileState m_curr_state = GuidedMissileState_None;
		Vector3 m_velocity;
		Ticker m_ticker;
		float m_last_elaspe_time = 0;
		int m_wait_frame_for_destroy = 0;
	};

	std::shared_ptr<SceneUnit> AddGuidedMissileToScene(const Vector2 &pos, Vector2 face_dir, GuidedMissileParam param);
}