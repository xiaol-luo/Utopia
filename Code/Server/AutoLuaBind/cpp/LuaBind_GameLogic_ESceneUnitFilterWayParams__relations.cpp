#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Common/Geometry/GeometryDefine.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"

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