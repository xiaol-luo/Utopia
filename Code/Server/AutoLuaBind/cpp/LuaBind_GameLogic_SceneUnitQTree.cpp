#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/Geometry/GeometryDefine.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitQTree(lua_State *L)
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
                std::string name = "SceneUnitQTree";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitQTree> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitQTree()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitQTree"; })				
						,"root", &GameLogic::SceneUnitQTree::root				
						,"max_layer", &GameLogic::SceneUnitQTree::max_layer				
						,"split_capacity", &GameLogic::SceneUnitQTree::split_capacity				
						,"max_split_body_layer", &GameLogic::SceneUnitQTree::max_split_body_layer				
						,"CreateNode", &GameLogic::SceneUnitQTree::CreateNode				
						,"ReleaseNode", &GameLogic::SceneUnitQTree::ReleaseNode				
						,"Init", &GameLogic::SceneUnitQTree::Init				
						,"Release", &GameLogic::SceneUnitQTree::Release				
						,"UpdateNodeUnit", &GameLogic::SceneUnitQTree::UpdateNodeUnit				
						,"CanSplitBody", &GameLogic::SceneUnitQTree::CanSplitBody				
						,"CanOwnChildren", &GameLogic::SceneUnitQTree::CanOwnChildren				
						,"FindUnits", &GameLogic::SceneUnitQTree::FindUnits
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "DEFAULT_MAX_LAYER";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitQTree::DEFAULT_MAX_LAYER);
					}				
					{
						std::string var_name = "DEFAULT_SPLIT_CAPACITY";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitQTree::DEFAULT_SPLIT_CAPACITY);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}