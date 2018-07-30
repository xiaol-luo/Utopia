#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacher.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScript.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaSubscribeSceneEventDetail(lua_State *L)
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
                std::string name = "LuaSubscribeSceneEventDetail";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaSubscribeSceneEventDetail> meta_table(
						sol::constructors<				
						GameLogic::LuaSubscribeSceneEventDetail(GameLogic::EffectScript *, EventDispacher *)
						>(),
						"__StructName__", sol::property([]() {return "LuaSubscribeSceneEventDetail"; })				
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
