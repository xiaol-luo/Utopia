#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Config/AutoCsvCode/effect/CsvEffectForceMoveConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config_CsvEffectForceMoveConfig(lua_State *L)
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
                std::string name = "CsvEffectForceMoveConfig";
				std::string name_space = "Config";

				{
					sol::usertype<Config::CsvEffectForceMoveConfig> meta_table(
						"__StructName__", sol::property([]() {return "CsvEffectForceMoveConfig"; })				
						,"id", &Config::CsvEffectForceMoveConfig::id				
						,"ignore_terrian", &Config::CsvEffectForceMoveConfig::ignore_terrian				
						,"result", &Config::CsvEffectForceMoveConfig::result				
						,"anchor", &Config::CsvEffectForceMoveConfig::anchor				
						,"angle", &Config::CsvEffectForceMoveConfig::angle				
						,"Init", &Config::CsvEffectForceMoveConfig::Init
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