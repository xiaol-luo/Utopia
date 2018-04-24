#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/FightParam.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitFightParam(lua_State *L)
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
                std::string name = "SceneUnitFightParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitFightParam> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitFightParam()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitFightParam"; })				
						,"GetParam", &GameLogic::SceneUnitFightParam::GetParam				
						,"GetParamFix", &GameLogic::SceneUnitFightParam::GetParamFix				
						,"AddBaseValue", &GameLogic::SceneUnitFightParam::AddBaseValue				
						,"RemoveBaseValue", &GameLogic::SceneUnitFightParam::RemoveBaseValue				
						,"AddBaseValueFix", &GameLogic::SceneUnitFightParam::AddBaseValueFix				
						,"RemoveBaseValueFix", &GameLogic::SceneUnitFightParam::RemoveBaseValueFix				
						,"AddExtraPercent", &GameLogic::SceneUnitFightParam::AddExtraPercent				
						,"RemoveExtraPercent", &GameLogic::SceneUnitFightParam::RemoveExtraPercent				
						,"AddExtraPercentFix", &GameLogic::SceneUnitFightParam::AddExtraPercentFix				
						,"RemoveExtraPercentFix", &GameLogic::SceneUnitFightParam::RemoveExtraPercentFix				
						,"AddExtraValue", &GameLogic::SceneUnitFightParam::AddExtraValue				
						,"RemoveExtraValue", &GameLogic::SceneUnitFightParam::RemoveExtraValue				
						,"AddExtraValueFix", &GameLogic::SceneUnitFightParam::AddExtraValueFix				
						,"RemoveExtraValueFix", &GameLogic::SceneUnitFightParam::RemoveExtraValueFix				
						,"Recal", &GameLogic::SceneUnitFightParam::Recal				
						,"GetValue", &GameLogic::SceneUnitFightParam::GetValue				
						,"RecalFix", &GameLogic::SceneUnitFightParam::RecalFix				
						,"GetValueFix", &GameLogic::SceneUnitFightParam::GetValueFix				
						,"AttachState", &GameLogic::SceneUnitFightParam::AttachState				
						,"DeattachState", &GameLogic::SceneUnitFightParam::DeattachState				
						,"IsStateActive", &GameLogic::SceneUnitFightParam::IsStateActive				
						,"IsDead", &GameLogic::SceneUnitFightParam::IsDead				
						,"IsBlind", &GameLogic::SceneUnitFightParam::IsBlind				
						,"IsDizzy", &GameLogic::SceneUnitFightParam::IsDizzy				
						,"IsSilence", &GameLogic::SceneUnitFightParam::IsSilence				
						,"GetHp", &GameLogic::SceneUnitFightParam::GetHp				
						,"AddHp", &GameLogic::SceneUnitFightParam::AddHp				
						,"GetMp", &GameLogic::SceneUnitFightParam::GetMp				
						,"AddMp", &GameLogic::SceneUnitFightParam::AddMp				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitFightParam::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}