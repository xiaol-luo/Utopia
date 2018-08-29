#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "ShareCode/Config/AutoCsvCode/effect/CsvEffectAttrsConfig.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"	
#include "GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_FightParamKV(lua_State *L)
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
                std::string name = "FightParamKV";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::FightParamKV> meta_table(
						sol::constructors<				
						GameLogic::FightParamKV(),				
						GameLogic::FightParamKV(GameLogic::FightParamAddType, NetProto::EFightParam, int, int)
						>(),
						"__StructName__", sol::property([]() {return "FightParamKV"; })				
						,"add_type", &GameLogic::FightParamKV::add_type				
						,"key", &GameLogic::FightParamKV::key				
						,"val", &GameLogic::FightParamKV::val				
						,"unique_id", &GameLogic::FightParamKV::unique_id				
						,"Attach", &GameLogic::FightParamKV::Attach				
						,"Deattach", &GameLogic::FightParamKV::Deattach
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