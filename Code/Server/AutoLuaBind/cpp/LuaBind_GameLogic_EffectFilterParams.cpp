#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "ShareCode/Config/AutoCsvCode/CsvConfigSets.h"	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectFilterConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectFilterParams(lua_State *L)
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
                std::string name = "EffectFilterParams";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectFilterParams> meta_table(
						"__StructName__", sol::property([]() {return "EffectFilterParams"; })				
						,"cfg", &GameLogic::EffectFilterParams::cfg				
						,"exclude_suids", &GameLogic::EffectFilterParams::exclude_suids
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