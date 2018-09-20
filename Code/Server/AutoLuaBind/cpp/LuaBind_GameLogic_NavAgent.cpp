#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavMesh.h"	
#include "recastnavigation/DetourCrowd/Include/DetourCrowd.h"	
#include "Logic/LogicModules/GameLogic/Scene/Navigation/NavAgent.h"	
#include "DetourNavMeshQuery.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_NavAgent(lua_State *L)
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
                std::string name = "NavAgent";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::NavAgent> meta_table(
						sol::constructors<				
						GameLogic::NavAgent(GameLogic::NavMesh *)
						>(),
						"__StructName__", sol::property([]() {return "NavAgent"; })				
						,"m_move_type", &GameLogic::NavAgent::m_move_type				
						,"m_desired_move_pos", &GameLogic::NavAgent::m_desired_move_pos				
						,"m_desired_move_dir", &GameLogic::NavAgent::m_desired_move_dir				
						,"SetMovedCb", &GameLogic::NavAgent::SetMovedCb				
						,"OnMoved", &GameLogic::NavAgent::OnMoved				
						,"GetPos", &GameLogic::NavAgent::GetPos				
						,"SetPos", &GameLogic::NavAgent::SetPos				
						,"GetAgentParams", &GameLogic::NavAgent::GetAgentParams				
						,"SetAgentParams", &GameLogic::NavAgent::SetAgentParams				
						,"Enable", &GameLogic::NavAgent::Enable				
						,"Disable", &GameLogic::NavAgent::Disable				
						,"IsEnable", &GameLogic::NavAgent::IsEnable				
						,"GetVelocity", &GameLogic::NavAgent::GetVelocity				
						,"GetMaxSpeed", &GameLogic::NavAgent::GetMaxSpeed				
						,"SetMaxSpeed", &GameLogic::NavAgent::SetMaxSpeed				
						,"TryMoveToPos", &GameLogic::NavAgent::TryMoveToPos				
						,"TryMoveToDir", &GameLogic::NavAgent::TryMoveToDir				
						,"StopMove", &GameLogic::NavAgent::StopMove				
						,"TryResumeMove", &GameLogic::NavAgent::TryResumeMove
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "INVALID_ID";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::NavAgent::INVALID_ID);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}