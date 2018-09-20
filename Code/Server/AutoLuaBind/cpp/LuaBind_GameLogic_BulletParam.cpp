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
	void LuaBind_GameLogic_BulletParam(lua_State *L)
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
                std::string name = "BulletParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::BulletParam> meta_table(
						"__StructName__", sol::property([]() {return "BulletParam"; })				
						,"target_type", &GameLogic::BulletParam::target_type				
						,"target_pos", &GameLogic::BulletParam::target_pos				
						,"target_su", &GameLogic::BulletParam::target_su				
						,"move_speed", &GameLogic::BulletParam::move_speed				
						,"max_alive_sec", &GameLogic::BulletParam::max_alive_sec				
						,"use_effect_param", &GameLogic::BulletParam::use_effect_param				
						,"calibre", &GameLogic::BulletParam::calibre				
						,"hit_filter_id", &GameLogic::BulletParam::hit_filter_id				
						,"model_id", &GameLogic::BulletParam::model_id				
						,"body_radius", &GameLogic::BulletParam::body_radius				
						,"hit_action", &GameLogic::BulletParam::hit_action				
						,"done_action", &GameLogic::BulletParam::done_action
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