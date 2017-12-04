#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include <unordered_map>
#include "Network/Protobuf/BattleEnum.pb.h"

namespace GameLogic
{
	class Skill;

	class SceneUnitSkills : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Skills;
	public:
		SceneUnitSkills();
		virtual ~SceneUnitSkills() override;

		uint64_t AddSkill(std::shared_ptr<Skill> skill, NetProto::ESkillSlot slot, NetProto::ESkillBar bar);
		void RemoveSkill(uint64_t skill_key);
		std::shared_ptr<Skill> GetSkill(uint64_t skill_key);
		std::shared_ptr<Skill> GetSlotSkill(NetProto::ESkillSlot  slot);
		std::shared_ptr<Skill> GetSlotSkill(NetProto::ESkillSlot  slot, NetProto::ESkillBar bar);
		
		void SetSlotLevel(NetProto::ESkillSlot  slot);
		void GetSlotLevel(NetProto::ESkillSlot  slot);
	

	protected:
		std::shared_ptr<Skill> m_slots[NetProto::ESkillSlot_ARRAYSIZE][NetProto::ESkillBar_ARRAYSIZE];
		int m_levels[NetProto::ESkillSlot_ARRAYSIZE];
	};
}
