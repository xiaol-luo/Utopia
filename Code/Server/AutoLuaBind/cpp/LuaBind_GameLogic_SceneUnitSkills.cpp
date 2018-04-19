#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "LogicModules/GameLogic/Scene/Skills/Skill.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitSkills(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SceneUnitSkills";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitSkills> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitSkills()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitSkills"; })				
						,"AddSkill", &GameLogic::SceneUnitSkills::AddSkill				
						,"RemoveSkill", &GameLogic::SceneUnitSkills::RemoveSkill				
						,"GetSkill", &GameLogic::SceneUnitSkills::GetSkill				
						,"GetSlotActiveSkill", &GameLogic::SceneUnitSkills::GetSlotActiveSkill				
						,"GetActiveSkill", &GameLogic::SceneUnitSkills::GetActiveSkill				
						,"GetSlotSkill", &GameLogic::SceneUnitSkills::GetSlotSkill				
						,"SetSlotLevel", &GameLogic::SceneUnitSkills::SetSlotLevel				
						,"GetSlotLevel", &GameLogic::SceneUnitSkills::GetSlotLevel				
						,"GetSlotMaxLevel", &GameLogic::SceneUnitSkills::GetSlotMaxLevel				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitSkills::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}