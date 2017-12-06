#include "Skill.h"
#include "GameLogic/Scene/Config/SkillConfig.h"

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

	}

	bool Skill::Begin()
	{
		if (!this->CheckCanCast())
			return false;

		m_state = NetProto::ESS_Preparing;
		m_state_span.Restart(m_lvl_cfg->preparing_span);
		this->SyncClient();
		return true;
	}
	void Skill::HeartBeat()
	{
		int old_state = m_state;
		if (this->IsRunning() && !m_state_span.InCd())
		{
			while (m_state < NetProto::ESS_End && !m_state_span.InCd())
			{
				switch (m_state)
				{
					case NetProto::ESS_Preparing:
					{
						if (this->CheckCanCast())
						{
							++m_state;
							m_state_span.Restart(m_lvl_cfg->releasing_span);
						}
						else
						{
							m_state = NetProto::ESS_End;
						}
					}
					break;
					case NetProto::ESS_Releasing:
					{
						if (this->CheckCanCast())
						{
							this->ReleaseEffects();
							++m_state;
						}
						else
						{
							m_state = NetProto::ESS_End;
						}
					}
					break;
					case NetProto::ESS_Using:
					{
						bool using_skill = false;
						if (using_skill)
						{

						}
						else
						{
							++m_state;
							m_state_span.Restart(m_lvl_cfg->lasting_span);
						}
					}
					break;
					case NetProto::ESS_Lasting:
					{
						++m_state;
					}
					break;
				}
			}
			if (m_state >= NetProto::ESS_End)
			{
				this->End();
			}
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

	void Skill::ReleaseEffects()
	{
		// TODO
	}

	void Skill::End()
	{
		m_state = NetProto::ESS_End;
		m_state_span.Restart(0);
	}
}

