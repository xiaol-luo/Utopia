#include "Skill.h"
#include "SkillConfig.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/NewScene.h"
#include "Common/Utils/NumUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "Network/Protobuf/BattleEnum.pb.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Effects/EffectBase.h"
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	Skill::Skill(const SkillConfig * cfg)
	{
		assert(cfg && cfg->max_level >= 0);
		m_cfg = cfg;
		m_lvl_cfg = cfg->level_cfgs[0];
	}

	Skill::~Skill()
	{

	}

	int Skill::GetSkillId()
	{
		return m_cfg->id;
	}

	std::shared_ptr<SceneUnit> Skill::GetCaster()
	{
		return m_su_skills->GetOwner()->shared_from_this();
	}

	bool Skill::SetLevel(int lvl)
	{
		if (lvl < 0 || lvl > m_cfg->max_level)
			return false;
		m_lvl_cfg = m_cfg->GetLvlCfg(lvl);
		return true;
	}

	int Skill::GetLevel()
	{
		return m_lvl_cfg->level;
	}

	int Skill::GetMaxLevel()
	{
		return m_cfg->max_level;
	}

	void Skill::SetParams(int64_t target_suid, Vector3 pos, Vector2 dir)
	{
		m_use_skill_param.Reset();
		m_use_skill_param.pos = m_su_skills->GetOwner()->GetTransform()->GetPos();

		switch (m_cfg->use_way)
		{
		case NetProto::ESkillUseWay_SceneUnit:
			{		
				std::shared_ptr<SceneUnit> target_su = m_su_skills->GetOwner()->GetScene()->GetUnit(target_suid);
				if (nullptr != target_su)
				{
					m_use_skill_param.target_suid = target_suid;
					m_use_skill_param.target_su = target_su;
					m_use_skill_param.pos = target_su->GetTransform()->GetPos();
					m_use_skill_param.dir = (m_use_skill_param.pos - m_su_skills->GetOwner()->GetTransform()->GetPos()).XZ();
					m_use_skill_param.face_dir = m_use_skill_param.dir;
				}
			}
			break;
			case NetProto::ESkillUseWay_Position:
			{
				m_use_skill_param.pos = pos;
				m_use_skill_param.dir = (m_use_skill_param.pos - m_su_skills->GetOwner()->GetTransform()->GetPos()).XZ();
				m_use_skill_param.face_dir = m_use_skill_param.dir;
			}
			case NetProto::ESkillUseWay_PosAndDir:
			{
				m_use_skill_param.pos = pos;
				m_use_skill_param.dir = dir;
				m_use_skill_param.face_dir = (m_use_skill_param.pos - m_su_skills->GetOwner()->GetTransform()->GetPos()).XZ();
			}
			break;
			case NetProto::ESkillUseWay_Direction:
			{
				m_use_skill_param.dir = dir;
				m_use_skill_param.face_dir = dir;
			}
			break;
		}
	}

	bool Skill::Begin()
	{
		if (!this->CheckCanCast())
			return false;

		m_state = NetProto::ESS_ReadyGo;
		m_stage_begin_ms = this->GetLogicMs();
		m_can_move = m_lvl_cfg->can_move;
		if (!m_can_move)
			m_su_skills->GetModule<SceneUnitFightParam>()->AttachState(NetProto::EFP_Immobilized);
		this->SyncClient();
		return true;
	}

	bool Skill::InCd()
	{
		int64_t now_ms = this->GetLogicMs();
		return now_ms < m_last_release_ms + m_lvl_cfg->cd;
	}

	void Skill::HeartBeat()
	{
		if (!IsRunning())
			return;

		int old_state = m_state;
		bool is_fail = false;
		long now_ms = this->GetLogicMs();
		do
		{
			// Ready状态
			if (NetProto::ESS_ReadyGo == m_state)
			{
				if (!this->CheckCanCast())
				{
					is_fail = true;
					break;
				}

				this->SetFaceDir();
				m_state = NetProto::ESS_Preparing;
				m_stage_begin_ms = now_ms;
			}

			// 吟唱
			if (NetProto::ESS_Preparing == m_state)
			{
				if (!this->CheckCanCast())
				{
					is_fail = true;
					break;
				}

				if (now_ms < m_stage_begin_ms + m_lvl_cfg->preparing_span)
					break;

				m_state = NetProto::ESS_Releasing;
				m_stage_begin_ms = now_ms;
			}

			// 前摇
			if (NetProto::ESS_Releasing == m_state)
			{
				if (!this->CheckCanCast())
				{
					is_fail = true;
					break;
				}

				int release_span = m_lvl_cfg->releasing_span;
				{
					// TODO:
				}
				release_span = NumUtil::GetInRange(release_span, 0, INT_MAX);
				if (now_ms < m_stage_begin_ms + release_span)
					break;

				// 扣魔法
				// 释放Efffect
				this->ReleaseEffects();
				
				m_state = NetProto::ESS_Guiding;
				m_stage_begin_ms = now_ms;
			}

			// 引导
			if (NetProto::ESS_Guiding == m_state)
			{
				bool is_guiding = false;
				{
					for (auto kv_pair : m_guide_effects)
					{
						if (kv_pair.second->IsGuiding())
						{
							is_guiding = true;
							break;
						}
					}
				}
				if (is_guiding)
					break;

				m_state = NetProto::ESS_Lasting;
				m_stage_begin_ms = now_ms;
			}

			// 后摇
			if (NetProto::ESS_Lasting == m_state)
			{
				if (now_ms < m_stage_begin_ms + m_lvl_cfg->lasting_span)
					break;

				m_state = NetProto::ESS_End;
				m_stage_begin_ms = now_ms;
			}
		} while (false);

		if (is_fail || NetProto::ESS_End == m_state)
		{
			this->End();
		}
		if (old_state != m_state)
		{
			this->SyncClient();
		}
	}

	bool Skill::IsRunning()
	{
		return m_state >= 0 && m_state < NetProto::ESS_End;
	}

	bool Skill::TryCancel()
	{
		if (!this->IsRunning())
			return true;

		if (this->CanCancel())
		{
			this->End();
			return true;
		}
		return false;
	}

	bool Skill::CanCancel()
	{
		bool ret = true;
		if (NetProto::ESS_Guiding == m_state)
		{
			bool can_cancel = true;
			for (auto kv_pair : m_guide_effects)
			{
				if (!kv_pair.second->CanCancelGuide())
				{
					ret = false;
					break;
				}
			}
		}
		return ret;
	}

	void Skill::SyncClient()
	{
		SyncClientMsg msg = this->GetPbMsg();
		m_su_skills->SendObservers(msg.protocol_id, msg.msg);
	}

	SyncClientMsg Skill::GetPbMsg()
	{
		NetProto::SceneUnitSkillAction *msg = m_su_skills->GetOwner()->GetScene()->CreateProtobuf<NetProto::SceneUnitSkillAction>();
		msg->set_su_id(m_su_skills->GetOwner()->GetId());
		{
			msg->set_skill_id(this->GetSkillId());
			msg->set_stage_begin_ms(this->GetStageBeginMs());
			msg->set_stage((NetProto::ESkillState)this->GetStage());
		}
		return std::move(SyncClientMsg(NetProto::PID_SceneUnitSkillAction, msg));
	}

	void Skill::AddGuideEffect(std::shared_ptr<EffectBase> effect)
	{
		if (nullptr == effect || effect->GetKey() <= 0)
			return;
		m_guide_effects.insert_or_assign(effect->GetKey(), effect);
	}

	void Skill::RemoveGuideEffect(uint64_t effect_key)
	{
		m_guide_effects.erase(effect_key);
	}

	void Skill::ClearGuideEffects()
	{
		m_guide_effects.clear();
	}

	bool Skill::CheckCanCast()
	{
		if (this->InCd())
			return false;
		
		std::shared_ptr<SceneUnitFightParam> su_fp = m_su_skills->GetModule<SceneUnitFightParam>();
		assert(su_fp);
		
		if (su_fp->GetMp() < m_lvl_cfg->consume_mp)
			return false;
		if (su_fp->IsSilence()|| su_fp->IsDizzy() || su_fp->IsDead())
			return false;

		if (NetProto::ESkillUseWay_SceneUnit == m_cfg->use_way)
		{
			std::shared_ptr<SceneUnit> target_su = m_use_skill_param.target_su.lock();
			if (nullptr == target_su)
				return false;
			if (!(m_cfg->target_types & 1 << target_su->GetUnitType()))
				return false;

			bool ret = false;
			if (!ret && m_cfg->target_relations & 1 << NetProto::ESceneUnitRelation_Self)
			{
				ret |= NetProto::ESceneUnitRelation_Self == m_su_skills->GetScene()->SceneUnitRelation(m_su_skills->GetOwner()->shared_from_this(), target_su);
			}
			if (!ret && m_cfg->target_relations & 1 << NetProto::ESceneUnitRelation_Friend)
			{
				ret |= NetProto::ESceneUnitRelation_Friend == m_su_skills->GetScene()->SceneUnitRelation(m_su_skills->GetOwner()->shared_from_this(), target_su);
			}
			if (!ret && m_cfg->target_relations & 1 << NetProto::ESceneUnitRelation_Enemy)
			{
				ret |= NetProto::ESceneUnitRelation_Enemy == m_su_skills->GetScene()->SceneUnitRelation(m_su_skills->GetOwner()->shared_from_this(), target_su);
			}
			if (!ret)
				return false;

			if (target_su->GetId() != m_su_skills->GetOwner()->GetId())
			{
				if (!GeometryUtils::InFlatDistance(target_su->GetTransform()->GetPos(), m_su_skills->GetOwner()->GetTransform()->GetPos(), m_lvl_cfg->cast_distance))
				{
					return false;
				}
			}
		}
		else if (NetProto::ESkillUseWay_PosAndDir == m_cfg->use_way || NetProto::ESkillUseWay_PosAndDir == m_cfg->use_way)
		{
			if (!GeometryUtils::InFlatDistance(m_use_skill_param.pos, m_su_skills->GetOwner()->GetTransform()->GetPos(), m_lvl_cfg->cast_distance))
			{
				return false;
			}
		}

		return true;
	}

	void Skill::SetFaceDir()
	{
		Vector2 face_dir = m_use_skill_param.face_dir;

		switch (m_cfg->use_way)
		{
			case NetProto::ESkillUseWay_SceneUnit:
			{
				std::shared_ptr<SceneUnit> target_su =  m_use_skill_param.target_su.lock();
				if (nullptr != target_su)
				{
					face_dir = (target_su->GetTransform()->GetPos() - m_su_skills->GetOwner()->GetTransform()->GetPos()).XZ();
				}
			}
			break;
			case NetProto::ESkillUseWay_Position:
			case NetProto::ESkillUseWay_PosAndDir:
			{
				face_dir = (m_use_skill_param.pos - m_su_skills->GetOwner()->GetTransform()->GetPos()).XZ();
			}
			break;
		}
		m_su_skills->GetOwner()->GetTransform()->SetFaceDir(face_dir, ESUFaceDir_Skill);
	}

	void Skill::ReleaseEffects()
	{
		// 设置cd
		m_last_release_ms = this->GetLogicMs();

		for (int effect_id : m_lvl_cfg->release_effect_ids)
		{
			SceneEffects *ses = m_su_skills->GetScene()->GetModule<SceneEffects>();
			std::shared_ptr<EffectBase> effect = ses->CreateEffect(effect_id);
			if (nullptr != effect)
			{
				UseEffectParam use_param;
				use_param.skill = this->shared_from_this();
				use_param.dir = m_use_skill_param.dir;
				use_param.pos = m_use_skill_param.pos;
				use_param.target_suid = m_use_skill_param.target_suid;
				effect->Begin(use_param);
			}
		}
	}

	void Skill::End()
	{
		m_use_skill_param.Reset();
		m_state = NetProto::ESS_End;
		m_stage_begin_ms = LONG_MAX;
		Vector2 face_dir = m_su_skills->GetOwner()->GetTransform()->GetFaceDir();
		m_su_skills->GetOwner()->GetTransform()->SetFaceDir(Vector2::zero, ESUFaceDir_Skill);
		m_su_skills->GetOwner()->GetTransform()->SetFaceDir(face_dir, ESUFaceDir_Move);
		if (!m_can_move)
			m_su_skills->GetModule<SceneUnitFightParam>()->DeattachState(NetProto::EFP_Immobilized);
		this->SyncClient();
	}

	int64_t Skill::GetLogicMs(int64_t delta_ms)
	{
		int64_t ret = m_su_skills->GetOwner()->GetScene()->GetLogicMs() + delta_ms;
		return ret;
	}
}

