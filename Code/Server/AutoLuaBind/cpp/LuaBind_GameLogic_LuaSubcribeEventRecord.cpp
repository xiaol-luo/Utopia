#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/EventDispatcher/EventDispacherProxy.h"	
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaSubcribeEventRecord(lua_State *L)
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
                std::string name = "LuaSubcribeEventRecord";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::LuaSubcribeEventRecord> meta_table(
						sol::constructors<				
						GameLogic::LuaSubcribeEventRecord()
						>(),
						"__StructName__", sol::property([]() {return "LuaSubcribeEventRecord"; })				
						,"event_id", &GameLogic::LuaSubcribeEventRecord::event_id				
						,"subscribe_id", &GameLogic::LuaSubcribeEventRecord::subscribe_id				
						,"head", &GameLogic::LuaSubcribeEventRecord::head
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