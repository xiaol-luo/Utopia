#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/GameLogicModule.h"	
#include "ShareCode/Common/Utils/Ticker.h"	
#include "GameLogic/Scene/NewScene.h"	
#include "GameLogic/Scene/TestScene.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_TestScene(lua_State *L)
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
                std::string name = "TestScene";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::TestScene> meta_table(
						sol::constructors<				
						GameLogic::TestScene(GameLogicModule *, std::basic_string<char, std::char_traits<char>, std::allocator<char> >)
						>(),
						"__StructName__", sol::property([]() {return "TestScene"; })				
						, sol::base_classes, sol::bases<
							GameLogic::NewScene 
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