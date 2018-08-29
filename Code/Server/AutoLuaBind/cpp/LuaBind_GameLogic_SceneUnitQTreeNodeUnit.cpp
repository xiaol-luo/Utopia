#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "ShareCode/Common/Geometry/GeometryDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitQTreeNodeUnit(lua_State *L)
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
                std::string name = "SceneUnitQTreeNodeUnit";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitQTreeNodeUnit> meta_table(
						"__StructName__", sol::property([]() {return "SceneUnitQTreeNodeUnit"; })				
						,"unit", &GameLogic::SceneUnitQTreeNodeUnit::unit				
						,"attached_qtree_nodes", &GameLogic::SceneUnitQTreeNodeUnit::attached_qtree_nodes				
						,"Deattach", &GameLogic::SceneUnitQTreeNodeUnit::Deattach				
						,"Attach", &GameLogic::SceneUnitQTreeNodeUnit::Attach
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