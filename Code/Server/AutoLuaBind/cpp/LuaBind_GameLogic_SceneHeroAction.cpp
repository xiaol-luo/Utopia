#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "Common/Utils/Ticker.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitAction/SceneHeroAction.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneHeroAction(lua_State *L)
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
                std::string name = "SceneHeroAction";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneHeroAction> meta_table(
						sol::constructors<				
						GameLogic::SceneHeroAction()
						>(),
						"__StructName__", sol::property([]() {return "SceneHeroAction"; })				
						,"Trace", &GameLogic::SceneHeroAction::Trace				
						,"MoveTo", &GameLogic::SceneHeroAction::MoveTo				
						,"CancelMove", &GameLogic::SceneHeroAction::CancelMove				
						,"UseSkill", &GameLogic::SceneHeroAction::UseSkill				
						,"CancelSkill", &GameLogic::SceneHeroAction::CancelSkill				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneHeroAction::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}