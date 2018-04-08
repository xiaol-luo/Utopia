#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectFilterConfig(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "CsvEffectFilterConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectFilterConfig> meta_table(
					"__StructName__", sol::property([]() {return "CsvEffectFilterConfig"; })				
						,"id", &Config::CsvEffectFilterConfig::id				
						,"limit_num", &Config::CsvEffectFilterConfig::limit_num				
						,"limit_num_priority", &Config::CsvEffectFilterConfig::limit_num_priority				
						,"unit_types", &Config::CsvEffectFilterConfig::unit_types				
						,"relations", &Config::CsvEffectFilterConfig::relations				
						,"anchor", &Config::CsvEffectFilterConfig::anchor				
						,"shape_circle", &Config::CsvEffectFilterConfig::shape_circle				
						,"shape_rect", &Config::CsvEffectFilterConfig::shape_rect				
						,"shape_sector", &Config::CsvEffectFilterConfig::shape_sector				
						,"Init", &Config::CsvEffectFilterConfig::Init
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