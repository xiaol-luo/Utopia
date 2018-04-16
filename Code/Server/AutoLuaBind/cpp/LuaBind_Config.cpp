#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Config/AutoCsvCode/skill/CsvSkillLevelConfig.h"

namespace SolLuaBind
{
	void LuaBind_Config(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "Config";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}