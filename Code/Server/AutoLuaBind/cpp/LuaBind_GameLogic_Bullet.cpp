#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "Logic/ShareCode/Common/Utils/Ticker.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "Logic/LogicModules/GameLogic/Scene/Skills/Skill.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/SceneDefine.h"	
#include "Logic/ShareCode/Common/Geometry/Vector2.h"	
#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitMissile.h"	
#include "Logic/LogicModules/GameLogic/Scene/Missile/SceneUnitBullet/Bullet.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_Bullet(lua_State *L)
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
                std::string name = "Bullet";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::Bullet> meta_table(
						sol::constructors<				
						GameLogic::Bullet()
						>(),
						"__StructName__", sol::property([]() {return "Bullet"; })				
						,"SetParam", &GameLogic::Bullet::SetParam				
						,"SetDone", &GameLogic::Bullet::SetDone				
						,"CollectPBInit", &GameLogic::Bullet::CollectPBInit				
						,"CollectPbMutable", &GameLogic::Bullet::CollectPbMutable				
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