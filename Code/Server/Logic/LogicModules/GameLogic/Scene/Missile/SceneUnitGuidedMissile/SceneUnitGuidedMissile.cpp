#include "SceneUnitGuidedMissile.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/Skills/Skill.h"

namespace GameLogic
{
	SceneUnitGuidedMissile::SceneUnitGuidedMissile() : SceneUnitMissile()
	{

	}

	SceneUnitGuidedMissile::~SceneUnitGuidedMissile()
	{
	}

	bool SceneUnitGuidedMissile::SetParam(const GuidedMissileParam &param)
	{
		if (GuidedMissileState_None != m_curr_state)
			return false;
		m_param = param;
		m_curr_state = GuidedMissileState_Ready;
		return true;
	}

	void SceneUnitGuidedMissile::OnAwake()
	{
		m_transform = this->GetModule<SceneUnitTransform>();
	}

	void SceneUnitGuidedMissile::OnUpdate()
	{
		if (GuidedMissileState_Ready == m_curr_state)
		{
			m_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, this->GetScene()));
			m_ticker.Restart(m_param.max_alive_sec);

			m_curr_state = GuidedMissileState_Moving;
			if (GuidedMissileParam::TargetType_Pos == m_param.target_type)
			{
				Vector3 linkVec3 = m_param.target_pos - m_transform->GetPos();
				linkVec3.y = 0;
				m_velocity = Vector3::Normalize(linkVec3) * m_param.move_speed;
			}
		}

		if (GuidedMissileState_Moving == m_curr_state)
		{
			// 移动
			if (GuidedMissileParam::TargetType_SceneUnit == m_param.target_type)
			{
				Vector3 linkVec3 = m_param.target_su->GetTransform()->GetPos() - m_transform->GetPos();
				linkVec3.y = 0;
				m_velocity = Vector3::Normalize(linkVec3) * m_param.move_speed;
			}

			float time_span = m_ticker.ElaspeTime() - m_last_elaspe_time;
			if (!m_ticker.InCd())
				time_span = m_ticker.GetCd() - m_last_elaspe_time;
			m_last_elaspe_time = m_ticker.ElaspeTime();

			Vector3 move_distance = m_velocity * time_span;
			Vector3 ret_pos = m_transform->GetPos() + move_distance;

			Vector3 nor1 = m_param.target_pos - m_transform->GetPos();
			Vector3 nor2 = ret_pos - m_param.target_pos;
			nor1.y = 0; nor2.y = 0;
			bool isHitPoint = false;
			if (nor2.SqrMagnitude() > FLT_MIN)
			{
				nor1.Normalize(); nor2.Normalize();
				if (Vector3::Dot(nor1, nor2) > 0) // 夹角小于90度，也即ret_pos越过了target_pos
					isHitPoint = true;
			}
			else
			{
				isHitPoint = true;
			}
			if (isHitPoint)
			{
				ret_pos = m_param.target_pos;
				m_curr_state = GuidedMissileState_Hit;
			}
			m_transform->SetLocalPos(ret_pos);
		}

		if (GuidedMissileState_Hit == m_curr_state)
		{
			// 释放技能
			std::shared_ptr<EffectBase> effect = \
				m_owner->GetScene()->GetModule<SceneEffects>()->CreateEffect(m_param.effect_ids[0]);
			if (nullptr != effect)
			{
				UseEffectParam effect_param = m_param.use_effect_param;
				effect_param.pos = m_transform->GetPos();
				if (nullptr != m_param.target_su)
					effect_param.target_suid = m_param.target_su->GetId();
				effect->Begin(effect_param);
				m_curr_state = GuidedMissileState_Done;
			}
		}

		if (!m_ticker.InCd() || GuidedMissileState_Done == m_curr_state)
			m_curr_state = GuidedMissileState_Destroy;

		if (GuidedMissileState_Destroy == m_curr_state)
		{
			++m_wait_frame_for_destroy;
			if (m_wait_frame_for_destroy > 1)
			{
				// 自我销毁
				m_curr_state = GuidedMissileState_AllFinish;
				m_owner->GetScene()->RemoveUnit(m_owner->GetId());
			}
		}
	}

	std::shared_ptr<SceneUnit> AddGuidedMissileToScene(const Vector2 &pos, Vector2 face_dir, GuidedMissileParam param)
	{
		auto su = std::make_shared<SceneUnit>();
		su->SetUnitType(NetProto::EsceneUnitType_Effect);
		su->SetModelId(1);
		auto sugm = su->AddModule(std::make_shared<SceneUnitGuidedMissile>());
		sugm->SetParam(param);
		su->GetTransform()->SetLocalPos(Vector3(pos));
		su->GetTransform()->SetFaceDir(face_dir, ESUFaceDir::ESUFaceDir_Move);
		auto scene = param.use_effect_param.skill->GetCaster()->GetScene();
		scene->AddUnit(su);
		return su;
	}
}