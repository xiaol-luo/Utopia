#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "Common/Geometry/Vector2.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_UseSkillParam(lua_State *L)
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
                std::string name = "UseSkillParam";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::UseSkillParam> meta_table(
						"__StructName__", sol::property([]() {return "UseSkillParam"; })				
						,"target_suid", &GameLogic::UseSkillParam::target_suid				
						,"target_su", &GameLogic::UseSkillParam::target_su				
						,"pos", &GameLogic::UseSkillParam::pos				
						,"dir", &GameLogic::UseSkillParam::dir				
						,"face_dir", &GameLogic::UseSkillParam::face_dir				
						,"Reset", &GameLogic::UseSkillParam::Reset
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