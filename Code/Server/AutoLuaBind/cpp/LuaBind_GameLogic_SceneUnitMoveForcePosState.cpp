#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveState.h"	
#include "Common/Geometry/Vector3.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMoveState/SceneUnitMoveForcePosState.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitMoveForcePosState(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = const Vector3 &;
				using TypeAlias_2 = float;
				using TypeAlias_3 = void;
				static TypeAlias_3 ForcePos1(GameLogic::SceneUnitMoveForcePosState &cls, TypeAlias_1 p1, TypeAlias_2 p2)
				{
					return cls.ForcePos(p1, p2);
				}
				using TypeAlias_4 = const Vector3 &;
				using TypeAlias_5 = void;
				static TypeAlias_5 ForcePos2(GameLogic::SceneUnitMoveForcePosState &cls, TypeAlias_4 p1)
				{
					return cls.ForcePos(p1);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SceneUnitMoveForcePosState";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitMoveForcePosState> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitMoveForcePosState(GameLogic::SceneUnitMove *)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitMoveForcePosState"; })				
						,"Enter", &GameLogic::SceneUnitMoveForcePosState::Enter				
						,"Exit", &GameLogic::SceneUnitMoveForcePosState::Exit				
						,"Update", &GameLogic::SceneUnitMoveForcePosState::Update				
						,"IsDone", &GameLogic::SceneUnitMoveForcePosState::IsDone				
						,"ForceDone", &GameLogic::SceneUnitMoveForcePosState::ForceDone				
						,"ForcePos", sol::overload(ForOverloadFns::ForcePos1, ForOverloadFns::ForcePos2)				
						, sol::base_classes, sol::bases<
							GameLogic::SceneUnitMoveState 
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