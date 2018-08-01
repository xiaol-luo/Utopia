#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillConfigBase.h"	
#include "LogicModules/GameLogic/Scene/Config/SceneAllConfig.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/Defines/SceneDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SkillBase(lua_State *L)
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
                std::string name = "SkillBase";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SkillBase> meta_table(
						sol::constructors<				
						GameLogic::SkillBase(const GameLogic::SkillConfigBase *)
						>(),
						"__StructName__", sol::property([]() {return "SkillBase"; })				
						,"GetSkillId", &GameLogic::SkillBase::GetSkillId				
						,"SetSkillKey", &GameLogic::SkillBase::SetSkillKey				
						,"GetSkillKey", &GameLogic::SkillBase::GetSkillKey				
						,"SetSceneUnitSkills", &GameLogic::SkillBase::SetSceneUnitSkills				
						,"GetSceneUnitSkills", &GameLogic::SkillBase::GetSceneUnitSkills				
						,"GetCaster", &GameLogic::SkillBase::GetCaster				
						,"GetLogicMs", &GameLogic::SkillBase::GetLogicMs				
						,"SetLevel", &GameLogic::SkillBase::SetLevel				
						,"ReloadCfg", &GameLogic::SkillBase::ReloadCfg				
						,"SyncClient", &GameLogic::SkillBase::SyncClient				
						,"GetPbMsg", &GameLogic::SkillBase::GetPbMsg				
						, sol::base_classes, sol::bases<
							std::enable_shared_from_this<GameLogic::SkillBase> 
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