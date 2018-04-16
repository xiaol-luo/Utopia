#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/ShareCode/Common/Geometry/GeometryDefine.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitQTreeNode(lua_State *L)
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
                std::string name = "SceneUnitQTreeNode";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitQTreeNode> meta_table(
						"__StructName__", sol::property([]() {return "SceneUnitQTreeNode"; })				
						,"area", &GameLogic::SceneUnitQTreeNode::area				
						,"layer", &GameLogic::SceneUnitQTreeNode::layer				
						,"tree", &GameLogic::SceneUnitQTreeNode::tree				
						,"children", &GameLogic::SceneUnitQTreeNode::children				
						,"node_units", &GameLogic::SceneUnitQTreeNode::node_units				
						,"FindUnits", &GameLogic::SceneUnitQTreeNode::FindUnits				
						,"AddUnit", &GameLogic::SceneUnitQTreeNode::AddUnit				
						,"HasChildren", &GameLogic::SceneUnitQTreeNode::HasChildren				
						,"Travel", &GameLogic::SceneUnitQTreeNode::Travel				
						,"GetNodeUnits", &GameLogic::SceneUnitQTreeNode::GetNodeUnits				
						,"GetNodeUnitCount", &GameLogic::SceneUnitQTreeNode::GetNodeUnitCount
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