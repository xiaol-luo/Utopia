#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"	
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeSceneUnitEventFnDetail.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaScribeSceneUnitEventFnDetail(lua_State *L)
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
                std::string name = "LuaScribeSceneUnitEventFnDetail";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaScribeSceneUnitEventFnDetail> meta_table(
						"__StructName__", sol::property([]() {return "LuaScribeSceneUnitEventFnDetail"; })				
						,"GetEventId", &GameLogic::LuaScribeSceneUnitEventFnDetail::GetEventId				
						,"GetSubscribeEventFn", &GameLogic::LuaScribeSceneUnitEventFnDetail::GetSubscribeEventFn				
						, sol::base_classes, sol::bases<
							GameLogic::LuaScribeEventFnDetail 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "s_allFnDetails";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::LuaScribeSceneUnitEventFnDetail::s_allFnDetails);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}