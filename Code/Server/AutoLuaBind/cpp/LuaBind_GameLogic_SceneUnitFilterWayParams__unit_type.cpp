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
	void LuaBind_GameLogic_SceneUnitFilterWayParams__unit_type(lua_State *L)
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
                std::string name = "_unit_type";
				std::string name_space = "GameLogic.SceneUnitFilterWayParams";

				{
					sol::usertype<GameLogic::SceneUnitFilterWayParams::_unit_type> meta_table(
						"__StructName__", sol::property([]() {return "_unit_type"; })				
						,"allow_types", &GameLogic::SceneUnitFilterWayParams::_unit_type::allow_types
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