#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_UseEffectParam(lua_State *L)
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
                std::string name = "UseEffectParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::UseEffectParam> meta_table(
						"__StructName__", sol::property([]() {return "UseEffectParam"; })				
						,"skill", &GameLogic::UseEffectParam::skill				
						,"use_skill_param", &GameLogic::UseEffectParam::use_skill_param				
						,"target_suid", &GameLogic::UseEffectParam::target_suid				
						,"pos", &GameLogic::UseEffectParam::pos				
						,"dir", &GameLogic::UseEffectParam::dir				
						,"Reset", &GameLogic::UseEffectParam::Reset
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