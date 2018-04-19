#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfig.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "LogicModules/GameLogic/Scene/Skills/Skill.h"	
#include "LogicModules/GameLogic/Scene/Defines/SceneDefine.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"

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
						,"GetSkillId", &GameLogic::Skill::GetSkillId				
						,"SetSceneUnitSkills", &GameLogic::Skill::SetSceneUnitSkills				
						,"GetSceneUnitSkills", &GameLogic::Skill::GetSceneUnitSkills				
						,"GetCaster", &GameLogic::Skill::GetCaster				
						,"SetLevel", &GameLogic::Skill::SetLevel				
						,"GetLevel", &GameLogic::Skill::GetLevel				
						,"GetMaxLevel", &GameLogic::Skill::GetMaxLevel				
						,"SetSkillKey", &GameLogic::Skill::SetSkillKey				
						,"GetSkillKey", &GameLogic::Skill::GetSkillKey				
						,"GetLvlCfg", &GameLogic::Skill::GetLvlCfg				
						,"GetCfg", &GameLogic::Skill::GetCfg				
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
							std::enable_shared_from_this<GameLogic::Skill> 
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