#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Utils/Ticker.h"	
#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitGuidedMissile/SceneUnitGuidedMissile.h"	
#include "Logic/LogicModules/GameLogic/Scene/Skills/Skill.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitMissile.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Common/Geometry/Vector3.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"	
#include "Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitGuidedMissile(lua_State *L)
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
                std::string name = "SceneUnitGuidedMissile";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitGuidedMissile> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitGuidedMissile()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitGuidedMissile"; })				
						,"SetParam", &GameLogic::SceneUnitGuidedMissile::SetParam				
						,"OnEnterScene", &GameLogic::SceneUnitGuidedMissile::OnEnterScene				
						,"OnUpdate", &GameLogic::SceneUnitGuidedMissile::OnUpdate				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitMissile 
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