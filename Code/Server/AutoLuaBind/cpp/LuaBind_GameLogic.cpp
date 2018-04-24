#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Defines/SceneDefine.h"	
#include "Common/Geometry/GeometryDefine.h"	
#include "recastnavigation/Recast/Include/Recast.h"	
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "protobuf/include/google/protobuf/message.h"	
#include "recastnavigation/DetourCrowd/Include/DetourCrowd.h"	
#include "Common/Geometry/Vector3.h"	
#include "recastnavigation/DetourTileCache/Include/DetourTileCache.h"	
#include "GameLogic/Scene/Navigation/NavMesh.h"	
#include "recastnavigation/Detour/Include/DetourNavMesh.h"	
#include "GameLogic/Scene/Navigation/NavMeshUtil.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/Defines/ViewDefine.h"	
#include "recastnavigation/Detour/Include/DetourNavMeshQuery.h"	
#include "recastnavigation/RecastDemo/Include/InputGeom.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "GameLogic";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "InvalidViewPos";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::InvalidViewPos);
				}				
				{
					std::string name = "VIEW_GRID_INVALID_IDX";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::VIEW_GRID_INVALID_IDX);
				}				
				{
					std::string name = "SCENE_UNIT_INVALID_ID";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::SCENE_UNIT_INVALID_ID);
				}				
				{
					std::string name = "MOVE_TO_POS_IGNORE_DISTANCE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::MOVE_TO_POS_IGNORE_DISTANCE);
				}				
				{
					std::string name = "MOVE_TO_POS_IGNORE_SQR_DISTANCE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::MOVE_TO_POS_IGNORE_SQR_DISTANCE);
				}				
				{
					std::string name = "GenerateEndEffectIdVec";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::GenerateEndEffectIdVec);
				}				
				{
					std::string name = "StrToEffectFilterAnchor";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::StrToEffectFilterAnchor);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}