#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"	
#include "GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_FightParamKVs(lua_State *L)
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
                std::string name = "FightParamKVs";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::FightParamKVs> meta_table(
						"__StructName__", sol::property([]() {return "FightParamKVs"; })				
						,"kvs", &GameLogic::FightParamKVs::kvs				
						,"Attach", &GameLogic::FightParamKVs::Attach				
						,"Deattach", &GameLogic::FightParamKVs::Deattach
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