#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigMgr.h"	
#include "ShareCode/Config/AutoCsvCode/CsvConfigSets.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectConfigMgr(lua_State *L)
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
                std::string name = "EffectConfigMgr";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectConfigMgr> meta_table(
						sol::constructors<				
						GameLogic::EffectConfigMgr()
						>(),
						"__StructName__", sol::property([]() {return "EffectConfigMgr"; })				
						,"LoadCfg", &GameLogic::EffectConfigMgr::LoadCfg				
						,"GetCfg", &GameLogic::EffectConfigMgr::GetCfg				
						,"GetAllCfg", &GameLogic::EffectConfigMgr::GetAllCfg
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