#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Config/AutoCsvCode/effect/CsvEffectFilterConfig.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectFilterConfig.h"	
#include "Config/AutoCsvCode/CsvConfigSets.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectFilterConfigMgr(lua_State *L)
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
                std::string name = "EffectFilterConfigMgr";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectFilterConfigMgr> meta_table(
						sol::constructors<				
						GameLogic::EffectFilterConfigMgr()
						>(),
						"__StructName__", sol::property([]() {return "EffectFilterConfigMgr"; })				
						,"LoadCfg", &GameLogic::EffectFilterConfigMgr::LoadCfg				
						,"GetCfg", &GameLogic::EffectFilterConfigMgr::GetCfg
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