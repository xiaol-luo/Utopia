#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "InputGeom.h"	
#include "DetourTileCache.h"	
#include "DetourNavMeshBuilder.h"	
#include "GameLogic/Scene/Navigation/NavMeshUtil.h"	
#include "DetourTileCacheBuilder.h"

namespace SolLuaBind
{
	void LuaBind_MeshProcess(lua_State *L)
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
                std::string name = "MeshProcess";
				std::string name_space = "";

				{
					sol::usertype<MeshProcess> meta_table(
						sol::constructors<				
						MeshProcess()
						>(),
						"__StructName__", sol::property([]() {return "MeshProcess"; })				
						,"m_geom", &MeshProcess::m_geom				
						,"init", &MeshProcess::init				
						,"process", &MeshProcess::process				
						, sol::base_classes, sol::bases<
							dtTileCacheMeshProcess 
						>()
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