#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "effect/CsvEffectHealConfig.h"	
#include "effect/CsvEffectGroupConfig.h"	
#include "log/CsvLogConfig.h"	
#include "effect/CsvEffectForceMoveConfig.h"	
#include "CsvConfigSets.h"	
#include "effect/CsvEffectSearcherConfig.h"	
#include "effect/CsvEffectHurtConfig.h"	
#include "effect/CsvEffectFilterConfig.h"	
#include "effect/CsvEffectAttrsConfig.h"	
#include "skill/CsvSkillConfig.h"	
#include "effect/CsvEffectScriptConfig.h"	
#include "Scene/CsvSceneConfig.h"	
#include "skill/CsvSkillLevelConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvConfigSets(lua_State *L)
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
						,"csv_CsvEffectScriptConfigSet", &Config::CsvConfigSets::csv_CsvEffectScriptConfigSet				
						,"csv_CsvEffectForceMoveConfigSet", &Config::CsvConfigSets::csv_CsvEffectForceMoveConfigSet				
						,"csv_CsvEffectSearcherConfigSet", &Config::CsvConfigSets::csv_CsvEffectSearcherConfigSet				
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