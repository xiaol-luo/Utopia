#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_TimeLineEffectIdsConfig(lua_State *L)
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
                std::string name = "TimeLineEffectIdsConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::TimeLineEffectIdsConfig> meta_table(
						"__StructName__", sol::property([]() {return "TimeLineEffectIdsConfig"; })				
						,"effect_ids", &GameLogic::TimeLineEffectIdsConfig::effect_ids				
						,"min_wait_ms", &GameLogic::TimeLineEffectIdsConfig::min_wait_ms				
						,"max_wait_ms", &GameLogic::TimeLineEffectIdsConfig::max_wait_ms				
						,"Generate", &GameLogic::TimeLineEffectIdsConfig::Generate
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