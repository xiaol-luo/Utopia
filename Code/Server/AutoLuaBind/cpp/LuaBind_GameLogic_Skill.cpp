#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/Defines/SceneDefine.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"	
#include "GameLogic/Scene/Skills/SkillBase.h"	
#include "GameLogic/Scene/Config/SceneAllConfig.h"	
#include "GameLogic/Scene/Skills/SkillConfig.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_Skill(lua_State *L)
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
                std::string name = "Skill";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::Skill> meta_table(
						sol::constructors<				
						GameLogic::Skill(const GameLogic::SkillConfig *)
						>(),
						"__StructName__", sol::property([]() {return "Skill"; })				
						,"SetLevel", &GameLogic::Skill::SetLevel				
						,"GetLevel", &GameLogic::Skill::GetLevel				
						,"GetMaxLevel", &GameLogic::Skill::GetMaxLevel				
						,"GetCfg", &GameLogic::Skill::GetCfg				
						,"ReloadCfg", &GameLogic::Skill::ReloadCfg				
						,"GetStage", &GameLogic::Skill::GetStage				
						,"GetStageBeginMs", &GameLogic::Skill::GetStageBeginMs				
						,"SetParams", &GameLogic::Skill::SetParams				
						,"Begin", &GameLogic::Skill::Begin				
						,"InCd", &GameLogic::Skill::InCd				
						,"HeartBeat", &GameLogic::Skill::HeartBeat				
						,"IsRunning", &GameLogic::Skill::IsRunning				
						,"TryCancel", &GameLogic::Skill::TryCancel				
						,"CanCancel", &GameLogic::Skill::CanCancel				
						,"SyncClient", &GameLogic::Skill::SyncClient				
						,"GetPbMsg", &GameLogic::Skill::GetPbMsg				
						,"AddGuideEffect", &GameLogic::Skill::AddGuideEffect				
						,"RemoveGuideEffect", &GameLogic::Skill::RemoveGuideEffect				
						,"ClearGuideEffects", &GameLogic::Skill::ClearGuideEffects				
						, sol::base_classes, sol::bases<
							GameLogic::SkillBase 
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