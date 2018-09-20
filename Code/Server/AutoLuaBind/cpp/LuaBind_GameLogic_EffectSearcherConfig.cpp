#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "effect/CsvEffectSearcherConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectSearcher/EffectSearcherConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectSearcherConfig(lua_State *L)
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
                std::string name = "EffectSearcherConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectSearcherConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectSearcherConfig"; })				
						,"m_effect_ids", &GameLogic::EffectSearcherConfig::m_effect_ids				
						,"m_is_extract", &GameLogic::EffectSearcherConfig::m_is_extract				
						,"CreateEffect", &GameLogic::EffectSearcherConfig::CreateEffect				
						,"InitCfg", &GameLogic::EffectSearcherConfig::InitCfg				
						, sol::base_classes, sol::bases<
							GameLogic::EffectConfigBase 
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