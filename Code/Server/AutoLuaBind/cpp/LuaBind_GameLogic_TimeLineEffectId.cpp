#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "ShareCode/Common/Geometry/Vector3.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_TimeLineEffectId(lua_State *L)
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
                std::string name = "TimeLineEffectId";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::TimeLineEffectId> meta_table(
						"__StructName__", sol::property([]() {return "TimeLineEffectId"; })				
						,"id", &GameLogic::TimeLineEffectId::id				
						,"wait_ms", &GameLogic::TimeLineEffectId::wait_ms				
						,"Generate", &GameLogic::TimeLineEffectId::Generate
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