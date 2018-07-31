#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvSceneConfig(lua_State *L)
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
                std::string name = "CsvSceneConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvSceneConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvSceneConfig"; })				
						,"id", &Config::CsvSceneConfig::id				
						,"terrain_file_path", &Config::CsvSceneConfig::terrain_file_path				
						,"Init", &Config::CsvSceneConfig::Init
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