#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaScribeSceneUnitEventFnParam(lua_State *L)
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
                std::string name = "LuaScribeSceneUnitEventFnParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaScribeSceneUnitEventFnParam> meta_table(
						"__StructName__", sol::property([]() {return "LuaScribeSceneUnitEventFnParam"; })				
						,"su", &GameLogic::LuaScribeSceneUnitEventFnParam::su				
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