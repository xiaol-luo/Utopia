#include "SceneUnitSkills.h"
#include "GameLogic/Scene/Skills/Skill.h"

namespace GameLogic
{
	SceneUnitSkills::SceneUnitSkills() : SceneUnitModule(MODULE_TYPE)
	{
	}

	SceneUnitSkills::~SceneUnitSkills()
	{
		for (auto &slot_array : m_slots)
		{
			for (int slot = 0; slot < NetProto::ESkillSlot_ARRAYSIZE; ++slot)
			{
				for (int bar = 0; bar < NetProto::ESkillBar_ARRAYSIZE; ++bar)
				{
					m_slots[slot][bar] = nullptr;
				}
			}
		}
	}

	uint64_t SceneUnitSkills::AddSkill(std::shared_ptr<Skill> skill, NetProto::ESkillSlot slot, NetProto::ESkillBar bar)
	{
		if (nullptr == skill || slot < NetProto::ESkillSlot_MIN || slot > NetProto::ESkillSlot_MAX ||
			bar < NetProto::ESkillBar_MIN || bar > NetProto::ESkillBar_MAX)
			return 0;

		++m_last_skill_key;
		skill->SetSkillKey(m_last_skill_key);
		skill->SetSceneUnitSkills(this->GetSharedPtr<SceneUnitSkills>());
		m_slots[slot][bar] = skill;
		// TODO : Sync client
		return m_last_skill_key;
	}

	void SceneUnitSkills::RemoveSkill(uint64_t skill_key)
	{
		for (int slot = 0; slot < NetProto::ESkillSlot_ARRAYSIZE; ++slot)
		{
			for (int bar = 0; bar < NetProto::ESkillBar_ARRAYSIZE; ++bar)
			{
				if (nullptr != m_slots[slot][bar] && m_slots[slot][bar]->GetSkillKey() == skill_key)
				{
					m_slots[slot][bar] = nullptr;
				}
			}
		}
	}

	std::shared_ptr<Skill> SceneUnitSkills::GetSkill(uint64_t skill_key)
	{
		for (int slot = 0; slot < NetProto::ESkillSlot_ARRAYSIZE; ++slot)
		{
			for (int bar = 0; bar < NetProto::ESkillBar_ARRAYSIZE; ++bar)
			{
				if (nullptr != m_slots[slot][bar] && m_slots[slot][bar]->GetSkillKey() == skill_key)
				{
					return m_slots[slot][bar];
				}
			}
		}
		return nullptr;
	}

	std::shared_ptr<Skill> SceneUnitSkills::GetSlotActiveSkill(NetProto::ESkillSlot slot)
	{
		if (slot < NetProto::ESkillSlot_MIN || slot > NetProto::ESkillSlot_MAX)
			return nullptr;

		std::shared_ptr<Skill> *skill_bar = m_slots[slot];
		for (int bar = NetProto::ESkillBar_MAX; bar >= NetProto::ESkillBar_MIN; --bar)
		{
			if (nullptr != skill_bar[bar])
				return skill_bar[bar];
		}
		return nullptr;
	}

	std::shared_ptr<Skill> SceneUnitSkills::GetActiveSkill(int skill_id)
	{
		for (int slot = 0; slot < NetProto::ESkillSlot_ARRAYSIZE; ++slot)
		{
			auto skill = this->GetSlotActiveSkill((NetProto::ESkillSlot)slot);
			if (nullptr != skill && skill_id == skill->GetSkillId())
				return skill;
		}
		return nullptr;
	}

	std::shared_ptr<Skill> SceneUnitSkills::GetSlotSkill(NetProto::ESkillSlot slot, NetProto::ESkillBar bar)
	{
		if (slot < NetProto::ESkillSlot_MIN || slot > NetProto::ESkillSlot_MAX ||
			bar < NetProto::ESkillBar_MIN || bar > NetProto::ESkillBar_MAX)
			return nullptr;
		return m_slots[slot][bar];
	}

	bool SceneUnitSkills::SetSlotLevel(NetProto::ESkillSlot slot,int level)
	{
		auto skill = this->GetSlotSkill(slot, NetProto::ESkillBar_Default);
		if (nullptr != skill)
		{
			// TODO: ?
			return skill->SetLevel(level);
		}
		return false;
	}

	int SceneUnitSkills::GetSlotLevel(NetProto::ESkillSlot slot)
	{
		auto skill = this->GetSlotSkill(slot, NetProto::ESkillBar_Default);
		if (nullptr == skill)
			return -1;
		return skill->GetLevel();
	}

	int SceneUnitSkills::GetSlotMaxLevel(NetProto::ESkillSlot slot)
	{
		auto skill = this->GetSlotSkill(slot, NetProto::ESkillBar_Default);
		if (nullptr == skill)
			return -1;
		return skill->GetMaxLevel();
	}
}
