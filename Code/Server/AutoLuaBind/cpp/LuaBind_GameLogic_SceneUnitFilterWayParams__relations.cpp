#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "ShareCode/Common/Geometry/GeometryDefine.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitFilterWayParams__relations(lua_State *L)
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
				std::string name_space = "GameLogic.SceneUnitFilterWayParams";

				{
					sol::usertype<GameLogic::SceneUnitFilterWayParams::_relations> meta_table(
						"__StructName__", sol::property([]() {return "_relations"; })				
						,"caster", &GameLogic::SceneUnitFilterWayParams::_relations::caster				
						,"relations", &GameLogic::SceneUnitFilterWayParams::_relations::relations
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