#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "ShareCode/Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_ESceneUnitFilterWayParams__relations(lua_State *L)
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
                std::string name = "_relations";
				std::string name_space = "GameLogic.ESceneUnitFilterWayParams";

				{
					sol::usertype<GameLogic::ESceneUnitFilterWayParams::_relations> meta_table(
						"__StructName__", sol::property([]() {return "_relations"; })				
						,"caster", &GameLogic::ESceneUnitFilterWayParams::_relations::caster				
						,"relations", &GameLogic::ESceneUnitFilterWayParams::_relations::relations
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