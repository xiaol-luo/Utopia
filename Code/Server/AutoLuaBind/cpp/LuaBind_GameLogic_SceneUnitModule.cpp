#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "LogicModules/GameLogic/Scene/NewScene.h"	
#include "Libs/3rdpartLibs/protobuf/include/google/protobuf/message.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitModule(lua_State *L)
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
                std::string name = "SceneUnitModule";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitModule> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitModule(GameLogic::ESceneUnitModule)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitModule"; })				
						,"GetOwner", &GameLogic::SceneUnitModule::GetOwner				
						,"GetScene", &GameLogic::SceneUnitModule::GetScene				
						,"GetModuleName", &GameLogic::SceneUnitModule::GetModuleName				
						,"GetId", &GameLogic::SceneUnitModule::GetId				
						,"GetEvProxy", &GameLogic::SceneUnitModule::GetEvProxy				
						,"GetSceneEvProxy", &GameLogic::SceneUnitModule::GetSceneEvProxy				
						,"SendSelf", &GameLogic::SceneUnitModule::SendSelf				
						,"SendSelfEx", &GameLogic::SceneUnitModule::SendSelfEx				
						,"SendObservers", &GameLogic::SceneUnitModule::SendObservers				
						,"SendObserversEx", &GameLogic::SceneUnitModule::SendObserversEx				
						, sol::base_classes, sol::bases<
							std::enable_shared_from_this<GameLogic::SceneUnitModule> 
						>()
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