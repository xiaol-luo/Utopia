#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectConfigBase(lua_State *L)
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
                std::string name = "EffectConfigBase";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectConfigBase> meta_table(
						"__StructName__", sol::property([]() {return "EffectConfigBase"; })				
						,"CreateEffect", &GameLogic::EffectConfigBase::CreateEffect				
						,"GetBeginEffectIds", &GameLogic::EffectConfigBase::GetBeginEffectIds				
						,"GetEndEffectIds", &GameLogic::EffectConfigBase::GetEndEffectIds				
						,"GetLoopEffectIds", &GameLogic::EffectConfigBase::GetLoopEffectIds				
						,"NeedGuide", &GameLogic::EffectConfigBase::NeedGuide				
						,"Reversible", &GameLogic::EffectConfigBase::Reversible				
						,"CanCancelGuide", &GameLogic::EffectConfigBase::CanCancelGuide				
						,"GetId", &GameLogic::EffectConfigBase::GetId				
						,"GetFilterId", &GameLogic::EffectConfigBase::GetFilterId				
						,"FinalCheck", &GameLogic::EffectConfigBase::FinalCheck
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