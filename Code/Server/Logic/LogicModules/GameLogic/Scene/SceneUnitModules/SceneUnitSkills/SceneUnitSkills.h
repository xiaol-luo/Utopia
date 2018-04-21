#pragma once

#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"
#include <unordered_map>
#include "Network/Protobuf/BattleEnum.pb.h"
#include <functional>

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
		std::shared_ptr<Skill> GetSlotActiveSkill(NetProto::ESkillSlot  slot);
		std::shared_ptr<Skill> GetActiveSkill(int skill_id);
		std::shared_ptr<Skill> GetSlotSkill(NetProto::ESkillSlot  slot, NetProto::ESkillBar bar);
		bool SetSlotLevel(NetProto::ESkillSlot  slot, int level);
		int GetSlotLevel(NetProto::ESkillSlot slot);
		int GetSlotMaxLevel(NetProto::ESkillSlot slot);
		void ForeachSkill(std::function<void(std::shared_ptr<Skill>, void* param)> fn, void *param);

	protected:
		std::shared_ptr<Skill> m_slots[NetProto::ESkillSlot_ARRAYSIZE][NetProto::ESkillBar_ARRAYSIZE];
		uint64_t m_last_skill_key = 0;
	};
}
