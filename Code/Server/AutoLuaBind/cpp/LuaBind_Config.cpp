#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Player/Player.h"	
#include "Scene/CsvSceneConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/SceneDefine.h"	
#include "Logic/LogicModules/GameLogic/GameLogicModule.h"	
#include "Logic/LogicModules/GameLogic/Scene/NewScene.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "protobuf/include/google/protobuf/arena.h"	
#include "protobuf/include/google/protobuf/message.h"	
#include "Logic/LogicModules/GameLogic/Scene/Config/SceneAllConfig.h"	
#include "Logic/ShareCode/Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_Config(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "Config";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}