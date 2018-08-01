#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectFilterConfig.h"	
#include "Config/AutoCsvCode/CsvConfigSets.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectFilterConfig(lua_State *L)
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
                std::string name = "EffectFilterConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectFilterConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectFilterConfig"; })				
						,"id", &GameLogic::EffectFilterConfig::id				
						,"limit_num", &GameLogic::EffectFilterConfig::limit_num				
						,"limit_num_priority", &GameLogic::EffectFilterConfig::limit_num_priority				
						,"unit_types", &GameLogic::EffectFilterConfig::unit_types				
						,"relations", &GameLogic::EffectFilterConfig::relations				
						,"anchor", &GameLogic::EffectFilterConfig::anchor				
						,"shape", &GameLogic::EffectFilterConfig::shape				
						,"shape_param", &GameLogic::EffectFilterConfig::shape_param				
						,"InitCfg", &GameLogic::EffectFilterConfig::InitCfg
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