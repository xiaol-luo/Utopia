#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfigBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SkillConfigBase(lua_State *L)
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
                std::string name = "SkillConfigBase";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SkillConfigBase> meta_table(
						"__StructName__", sol::property([]() {return "SkillConfigBase"; })				
						,"id", &GameLogic::SkillConfigBase::id				
						,"name", &GameLogic::SkillConfigBase::name
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