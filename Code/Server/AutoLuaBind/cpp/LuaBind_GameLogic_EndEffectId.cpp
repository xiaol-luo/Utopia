#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "Logic/LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "Logic/ShareCode/Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EndEffectId(lua_State *L)
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
                std::string name = "EndEffectId";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EndEffectId> meta_table(
						"__StructName__", sol::property([]() {return "EndEffectId"; })				
						,"end_case", &GameLogic::EndEffectId::end_case				
						,"id", &GameLogic::EndEffectId::id				
						,"Generate", &GameLogic::EndEffectId::Generate
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