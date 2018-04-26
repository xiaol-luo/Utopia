#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/Scene/CsvSceneConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvSceneConfigSet(lua_State *L)
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
                std::string name = "CsvSceneConfigSet";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvSceneConfigSet> meta_table(
						"__StructName__", sol::property([]() {return "CsvSceneConfigSet"; })				
						,"cfg_check_fun", &Config::CsvSceneConfigSet::cfg_check_fun				
						,"cfg_set_check_fun", &Config::CsvSceneConfigSet::cfg_set_check_fun				
						,"cfg_vec", &Config::CsvSceneConfigSet::cfg_vec				
						,"id_to_key", &Config::CsvSceneConfigSet::id_to_key				
						,"Load", &Config::CsvSceneConfigSet::Load
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