#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "GameLogic/Scene/NewScene.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectBase(lua_State *L)
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
                std::string name = "EffectBase";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectBase> meta_table(
						sol::constructors<				
						GameLogic::EffectBase(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, unsigned long long)
						>(),
						"__StructName__", sol::property([]() {return "EffectBase"; })				
						,"GetKey", &GameLogic::EffectBase::GetKey				
						,"GetCfg", &GameLogic::EffectBase::GetCfg				
						,"GetSkill", &GameLogic::EffectBase::GetSkill				
						,"GetCaster", &GameLogic::EffectBase::GetCaster				
						,"GetEffectTarget", &GameLogic::EffectBase::GetEffectTarget				
						,"Begin", &GameLogic::EffectBase::Begin				
						,"End", &GameLogic::EffectBase::End				
						,"Loop", &GameLogic::EffectBase::Loop				
						,"IsGuiding", &GameLogic::EffectBase::IsGuiding				
						,"CanCancelGuide", &GameLogic::EffectBase::CanCancelGuide				
						,"CanCelGuide", &GameLogic::EffectBase::CanCelGuide				
						, sol::base_classes, sol::bases<
							std::enable_shared_from_this<GameLogic::EffectBase> 
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