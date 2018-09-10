#pragma once

#include "GameLogic/Scene/Missile/SceneUnitMissile.h"
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Common/Utils/Ticker.h"
#include <sol.hpp>

namespace GameLogic
{
	class Skill;

	enum EBulletTarget
	{
		EBulletTarget_Pos,
		EBulletTarget_SceneUnit,
	};

	enum EBulletState
	{
		EBulletState_None = 0,
		EBulletState_Ready,
		EBulletState_Moving,
		EBulletState_Done,
		EBulletState_Destroying,
		EBulletState_AllFinish,
	};

	struct BulletParam
	{
		EBulletTarget target_type;
		Vector3 target_pos;
		std::shared_ptr<SceneUnit> target_su;
		float move_speed;
		float max_alive_sec = 20.0f;
		UseEffectParam use_effect_param;
		float calibre = 0.0f; // �ӵ��ھ�
		float hit_filter_id = 0; // ���й�����
		int model_id = 1; // ģ��id���ͻ����ð�
		float body_radius = 1.0f; // SceneUnitBody������뾶����
		sol::protected_function hit_action; // ������Ϊ
		sol::protected_function done_action; // ������Ϊ
	};

	class Bullet : public SceneUnitMissile
	{
	public:
		Bullet();
		virtual ~Bullet() override;

		bool SetParam(const BulletParam &param);
		void SetDone();

		virtual std::vector<SyncClientMsg> CollectPBInit() override;
		virtual std::vector<SyncClientMsg> CollectPbMutable() override;

	protected:
		void virtual OnEnterScene() override;
		virtual void OnUpdate() override;

		void SyncTargetPos();

	protected:
		BulletParam m_param;
		std::shared_ptr<SceneUnitTransform> m_transform;
		EBulletState m_curr_state = EBulletState_None;
		Vector3 m_velocity;
		Vector3 m_target_pos;
		Ticker m_ticker;
		float m_last_elaspe_sec = 0;
		int m_wait_frame_for_destory = 0;
	};

	std::shared_ptr<SceneUnit> AddBulletToScene(const Vector3 &pos, const Vector2 &face_dir, const BulletParam &param);
}