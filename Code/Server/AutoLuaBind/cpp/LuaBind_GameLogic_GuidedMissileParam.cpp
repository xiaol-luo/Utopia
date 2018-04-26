#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "ShareCode/Common/Utils/Ticker.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/Missile/SceneUnitMissile.h"	
#include "LogicModules/GameLogic/Scene/Skills/Skill.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"	
#include "LogicModules/GameLogic/Scene/Missile/SceneUnitGuidedMissile/SceneUnitGuidedMissile.h"

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
						,"maxAliveSec", &GameLogic::GuidedMissileParam::maxAliveSec				
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