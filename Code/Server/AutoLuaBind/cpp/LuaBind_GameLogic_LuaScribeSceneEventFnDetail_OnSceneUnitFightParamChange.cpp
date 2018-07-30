#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/EventDispatcher/EventDispacherProxy.h"	
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaSubscribeSceneEventFnDetail.h"	
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange(lua_State *L)
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
                std::string name = "LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange> meta_table(
						"__StructName__", sol::property([]() {return "LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange"; })				
						,"GetEventId", &GameLogic::LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetEventId				
						,"GetLuaFunName", &GameLogic::LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetLuaFunName				
						,"GetSubscribeEventFn", &GameLogic::LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange::GetSubscribeEventFn				
						, sol::base_classes, sol::bases<
							GameLogic::LuaScribeSceneEventFnDetail 
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