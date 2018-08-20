#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/Missile/SceneUnitGuidedMissile/SceneUnitGuidedMissile.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "Common/Utils/Ticker.h"	
#include "GameLogic/Scene/Missile/SceneUnitMissile.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_GuidedMissileParam(lua_State *L)
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
                std::string name = "GuidedMissileParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::GuidedMissileParam> meta_table(
						"__StructName__", sol::property([]() {return "GuidedMissileParam"; })				
						,"target_type", &GameLogic::GuidedMissileParam::target_type				
						,"target_pos", &GameLogic::GuidedMissileParam::target_pos				
						,"target_su", &GameLogic::GuidedMissileParam::target_su				
						,"move_speed", &GameLogic::GuidedMissileParam::move_speed				
						,"max_alive_sec", &GameLogic::GuidedMissileParam::max_alive_sec				
						,"use_effect_param", &GameLogic::GuidedMissileParam::use_effect_param				
						,"effect_ids", &GameLogic::GuidedMissileParam::effect_ids
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