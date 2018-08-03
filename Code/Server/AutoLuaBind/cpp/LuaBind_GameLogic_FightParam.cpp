#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/FightParam.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_FightParam(lua_State *L)
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
                std::string name = "FightParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::FightParam> meta_table(
						sol::constructors<				
						GameLogic::FightParam()
						>(),
						"__StructName__", sol::property([]() {return "FightParam"; })				
						,"SetFightParam", &GameLogic::FightParam::SetFightParam				
						,"SetPercentAsDenominator", &GameLogic::FightParam::SetPercentAsDenominator				
						,"SetBaseValueCalStrategy", &GameLogic::FightParam::SetBaseValueCalStrategy				
						,"SetBaseValueMin", &GameLogic::FightParam::SetBaseValueMin				
						,"SetBaseValueMax", &GameLogic::FightParam::SetBaseValueMax				
						,"AddBaseValue", &GameLogic::FightParam::AddBaseValue				
						,"RemoveBaseValue", &GameLogic::FightParam::RemoveBaseValue				
						,"SetExtraPercentCalStrategy", &GameLogic::FightParam::SetExtraPercentCalStrategy				
						,"SetExtraPercentMin", &GameLogic::FightParam::SetExtraPercentMin				
						,"SetExtraPercentMax", &GameLogic::FightParam::SetExtraPercentMax				
						,"AddExtraPercent", &GameLogic::FightParam::AddExtraPercent				
						,"RemoveExtraPercent", &GameLogic::FightParam::RemoveExtraPercent				
						,"SetExtraValueCalStrategy", &GameLogic::FightParam::SetExtraValueCalStrategy				
						,"SetExtraValueMin", &GameLogic::FightParam::SetExtraValueMin				
						,"SetExtraValueMax", &GameLogic::FightParam::SetExtraValueMax				
						,"AddExtraValue", &GameLogic::FightParam::AddExtraValue				
						,"RemoveExtraValue", &GameLogic::FightParam::RemoveExtraValue				
						,"SetMinValue", &GameLogic::FightParam::SetMinValue				
						,"SetMaxValue", &GameLogic::FightParam::SetMaxValue				
						,"Recal", &GameLogic::FightParam::Recal				
						,"GetFightParam", &GameLogic::FightParam::GetFightParam				
						,"GetValue", &GameLogic::FightParam::GetValue				
						,"SetValueChangeCallback", &GameLogic::FightParam::SetValueChangeCallback
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