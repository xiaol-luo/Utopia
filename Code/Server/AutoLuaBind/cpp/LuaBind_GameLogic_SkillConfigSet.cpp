#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Skills/SkillConfig.h"	
#include "GameLogic/Scene/Skills/SkillConfigBase.h"	
#include "CsvConfigSets.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SkillConfigSet(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = int;
				using TypeAlias_2 = const GameLogic::SkillConfig *;
				static TypeAlias_2 GetSkill1(const GameLogic::SkillConfigSet &cls, TypeAlias_1 p1)
				{
					return cls.GetSkill(p1);
				}
				using TypeAlias_3 = int;
				using TypeAlias_4 = int;
				using TypeAlias_5 = const GameLogic::SkillLevelConfig *;
				static TypeAlias_5 GetSkill2(const GameLogic::SkillConfigSet &cls, TypeAlias_3 p1, TypeAlias_4 p2)
				{
					return cls.GetSkill(p1, p2);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SkillConfigSet";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SkillConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "SkillConfigSet"; })				
						,"skills", &GameLogic::SkillConfigSet::skills				
						,"Reset", &GameLogic::SkillConfigSet::Reset				
						,"LoadCfg", &GameLogic::SkillConfigSet::LoadCfg				
						,"GetSkill", sol::overload(ForOverloadFns::GetSkill1, ForOverloadFns::GetSkill2)
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}