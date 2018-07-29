#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectGroupConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectGroupConfig(lua_State *L)
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
                std::string name = "CsvEffectGroupConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectGroupConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectGroupConfig"; })				
						,"id", &Config::CsvEffectGroupConfig::id				
						,"begin_effect_ids", &Config::CsvEffectGroupConfig::begin_effect_ids				
						,"end_effect_ids", &Config::CsvEffectGroupConfig::end_effect_ids				
						,"timeline_effect_ids", &Config::CsvEffectGroupConfig::timeline_effect_ids				
						,"need_guide", &Config::CsvEffectGroupConfig::need_guide				
						,"can_cancel_guide", &Config::CsvEffectGroupConfig::can_cancel_guide				
						,"Init", &Config::CsvEffectGroupConfig::Init
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