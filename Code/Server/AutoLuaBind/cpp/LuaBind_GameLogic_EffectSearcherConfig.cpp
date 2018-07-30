#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/Effects/EffectSearcher/EffectSearcherConfig.h"	
#include "effect/CsvEffectSearcherConfig.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"

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