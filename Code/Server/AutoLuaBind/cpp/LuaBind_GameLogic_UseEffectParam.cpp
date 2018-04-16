#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

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