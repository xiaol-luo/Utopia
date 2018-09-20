#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "Logic/ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "Logic/ShareCode/Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaSubscribeEventDetail(lua_State *L)
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
                std::string name = "LuaSubscribeEventDetail";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaSubscribeEventDetail> meta_table(
						sol::constructors<				
						GameLogic::LuaSubscribeEventDetail(sol::basic_table_core<false, sol::basic_reference<false> > *, EventDispacher *)
						>(),
						"__StructName__", sol::property([]() {return "LuaSubscribeEventDetail"; })				
						,"Subscribe", &GameLogic::LuaSubscribeEventDetail::Subscribe				
						,"Remove", &GameLogic::LuaSubscribeEventDetail::Remove				
						,"ClearAll", &GameLogic::LuaSubscribeEventDetail::ClearAll
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