#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavMeshUtil.h"	
#include "DetourNavMeshBuilder.h"	
#include "recastnavigation/RecastDemo/Include/InputGeom.h"	
#include "recastnavigation/DetourTileCache/Include/DetourTileCacheBuilder.h"	
#include "recastnavigation/DetourTileCache/Include/DetourTileCache.h"

namespace SolLuaBind
{
	void LuaBind_FastLZCompressor(lua_State *L)
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
                std::string name = "FastLZCompressor";
				std::string name_space = "";

				{
					sol::usertype<FastLZCompressor> meta_table(
						"__StructName__", sol::property([]() {return "FastLZCompressor"; })				
						,"maxCompressedSize", &FastLZCompressor::maxCompressedSize				
						,"compress", &FastLZCompressor::compress				
						,"decompress", &FastLZCompressor::decompress				
						, sol::base_classes, sol::bases<
							dtTileCacheCompressor 
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