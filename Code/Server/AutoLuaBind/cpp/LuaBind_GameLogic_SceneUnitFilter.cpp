#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "Common/Geometry/GeometryDefine.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitFilter(lua_State *L)
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
                std::string name = "SceneUnitFilter";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitFilter> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitFilter()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitFilter"; })				
						, sol::base_classes, sol::bases<
							GameLogic::SceneModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitFilter::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}