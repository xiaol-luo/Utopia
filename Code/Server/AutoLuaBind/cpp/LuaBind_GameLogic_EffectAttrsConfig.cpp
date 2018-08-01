#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectAttrsConfig(lua_State *L)
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
                std::string name = "EffectAttrsConfig";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectAttrsConfig> meta_table(
						"__StructName__", sol::property([]() {return "EffectAttrsConfig"; })				
						,"CreateEffect", &GameLogic::EffectAttrsConfig::CreateEffect				
						,"InitCfg", &GameLogic::EffectAttrsConfig::InitCfg				
						,"GetHoldTime", &GameLogic::EffectAttrsConfig::GetHoldTime				
						,"GetUniqueId", &GameLogic::EffectAttrsConfig::GetUniqueId				
						,"GetFightParamKvs", &GameLogic::EffectAttrsConfig::GetFightParamKvs				
						, sol::base_classes, sol::bases<
							GameLogic::EffectConfigBase 
						>()
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