#include "Skill.h"
#include "GameLogic/Scene/Config/SkillConfig.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/NewScene.h"
#include "Common/Utils/NumUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"

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
		this->ResetParams();
		switch (m_cfg->target_case)
		{
			case NetProto::ESkillTarget_Target:
			{
				m_target_suid = target_suid;
				m_target_su = m_su_skills->GetOwner()->GetScene()->GetUnit(target_suid);
			}
			break;
			case NetProto::ESkillTarget_Position:
			{
				m_pos = pos;
			}
			break;
			case NetProto::ESkillTarget_Direction:
			{
				m_dir = dir;
				if (m_dir == Vector2::zero)
					m_dir = Vector2::up;
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
				if (this->CheckCanCast())
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
				if (this->CheckCanCast())
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
				if (this->CheckCanCast())
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
				
				m_state = NetProto::ESS_Using;
				m_stage_begin_ms = now_ms;
			}

			// 引导
			if (NetProto::ESS_Using == m_state)
			{
				bool is_using = false;
				{
					// TODO:
				}
				if (is_using)
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
		if (!IsRunning())
			return true;

		// TODO
		this->End();
		this->SyncClient();
		return true;
	}

	void Skill::SyncClient()
	{
	}

	bool Skill::CheckCanCast()
	{
		return true;
	}

	void Skill::SetFaceDir()
	{
	}

	void Skill::ReleaseEffects()
	{
		// TODO
	}

	void Skill::End()
	{
		this->ResetParams();
		m_state = NetProto::ESS_End;
		m_stage_begin_ms = LONG_MAX;
		Vector2 face_dir = m_su_skills->GetOwner()->GetTransform()->GetFaceDir();
		m_su_skills->GetOwner()->GetTransform()->SetFaceDir(Vector2::zero, ESUFaceDir_Skill);
		m_su_skills->GetOwner()->GetTransform()->SetFaceDir(face_dir, ESUFaceDir_Move);
		if (!m_can_move)
			m_su_skills->GetModule<SceneUnitFightParam>()->DeattachState(NetProto::EFP_Immobilized);
	}
	void Skill::ResetParams()
	{
		m_target_suid = 0;
		m_target_su.reset();
		m_dir = Vector2::zero;
		m_pos = Vector3::zero;
	}
	long Skill::GetLogicMs(long delta_ms)
	{
		long ret = m_su_skills->GetOwner()->GetScene()->GetLogicMs() + delta_ms;
		return ret;
	}
}

