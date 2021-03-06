#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"	
#include "effect/CsvEffectAttrsConfig.h"

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