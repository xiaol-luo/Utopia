#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Config/AutoCsvCode/CsvConfigSets.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvConfigSets(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "CsvConfigSets";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvConfigSets> meta_table(
					"__StructName__", sol::property([]() {return "CsvConfigSets"; })				
						,"csv_CsvLogConfigSet", &Config::CsvConfigSets::csv_CsvLogConfigSet				
						,"csv_CsvSceneConfigSet", &Config::CsvConfigSets::csv_CsvSceneConfigSet				
						,"csv_CsvSkillConfigSet", &Config::CsvConfigSets::csv_CsvSkillConfigSet				
						,"csv_CsvSkillLevelConfigSet", &Config::CsvConfigSets::csv_CsvSkillLevelConfigSet				
						,"csv_CsvEffectHurtConfigSet", &Config::CsvConfigSets::csv_CsvEffectHurtConfigSet				
						,"csv_CsvEffectHealConfigSet", &Config::CsvConfigSets::csv_CsvEffectHealConfigSet				
						,"csv_CsvEffectAttrsConfigSet", &Config::CsvConfigSets::csv_CsvEffectAttrsConfigSet				
						,"csv_CsvEffectFilterConfigSet", &Config::CsvConfigSets::csv_CsvEffectFilterConfigSet				
						,"csv_CsvEffectGroupConfigSet", &Config::CsvConfigSets::csv_CsvEffectGroupConfigSet				
						,"Load", &Config::CsvConfigSets::Load
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