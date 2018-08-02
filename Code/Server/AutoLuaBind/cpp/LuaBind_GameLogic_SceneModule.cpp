#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/EventDispatcher/EventDispacherProxy.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "Logic/LogicModules/GameLogic/Scene/NewScene.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneModule(lua_State *L)
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
                std::string name = "SceneModule";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneModule> meta_table(
						sol::constructors<				
						GameLogic::SceneModule(GameLogic::ESceneModule)
						>(),
						"__StructName__", sol::property([]() {return "SceneModule"; })				
						,"GetModuleName", &GameLogic::SceneModule::GetModuleName				
						,"GetScene", &GameLogic::SceneModule::GetScene				
						,"GetSceneEvProxy", &GameLogic::SceneModule::GetSceneEvProxy
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