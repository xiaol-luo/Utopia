#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/NewScene.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "Common/EventDispatcher/EventDispacherProxy.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "GameLogic/Scene/Skills/SkillBase.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

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
						GameLogic::EffectBase(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, uint64_t)
						>(),
						"__StructName__", sol::property([]() {return "EffectBase"; })				
						,"GetKey", &GameLogic::EffectBase::GetKey				
						,"GetCfg", &GameLogic::EffectBase::GetCfg				
						,"GetSkill", &GameLogic::EffectBase::GetSkill				
						,"GetCaster", &GameLogic::EffectBase::GetCaster				
						,"GetEffectTarget", &GameLogic::EffectBase::GetEffectTarget				
						,"GetSkillTarget", &GameLogic::EffectBase::GetSkillTarget				
						,"GetScene", &GameLogic::EffectBase::GetScene				
						,"GetSceneUnit", &GameLogic::EffectBase::GetSceneUnit				
						,"GetUseEffectParam", &GameLogic::EffectBase::GetUseEffectParam				
						,"Begin", &GameLogic::EffectBase::Begin				
						,"End", &GameLogic::EffectBase::End				
						,"Loop", &GameLogic::EffectBase::Loop				
						,"IsGuiding", &GameLogic::EffectBase::IsGuiding				
						,"CanCancelGuide", &GameLogic::EffectBase::CanCancelGuide				
						,"CancelGuide", &GameLogic::EffectBase::CancelGuide				
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