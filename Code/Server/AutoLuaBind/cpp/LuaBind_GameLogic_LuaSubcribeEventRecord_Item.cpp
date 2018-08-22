#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaSubcribeEventRecord_Item(lua_State *L)
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
                std::string name = "Item";
				std::string name_space = "GameLogic.LuaSubcribeEventRecord";

				{
					sol::usertype<GameLogic::LuaSubcribeEventRecord::Item> meta_table(
						"__StructName__", sol::property([]() {return "Item"; })				
						,"id", &GameLogic::LuaSubcribeEventRecord::Item::id				
						,"fn", &GameLogic::LuaSubcribeEventRecord::Item::fn				
						,"pre", &GameLogic::LuaSubcribeEventRecord::Item::pre				
						,"next", &GameLogic::LuaSubcribeEventRecord::Item::next
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