#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/EventDispatcher/EventDispacherProxy.h"	
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaSubscribeSceneEventFnDetail.h"	
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaScribeSceneEventFnDetail(lua_State *L)
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
                std::string name = "LuaScribeSceneEventFnDetail";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaScribeSceneEventFnDetail> meta_table(
						"__StructName__", sol::property([]() {return "LuaScribeSceneEventFnDetail"; })				
						,"GetEventId", &GameLogic::LuaScribeSceneEventFnDetail::GetEventId				
						,"GetLuaFunName", &GameLogic::LuaScribeSceneEventFnDetail::GetLuaFunName				
						,"GetSubscribeEventFn", &GameLogic::LuaScribeSceneEventFnDetail::GetSubscribeEventFn
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "s_allFnDetails";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::LuaScribeSceneEventFnDetail::s_allFnDetails);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}