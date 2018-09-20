#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Defines/SceneDefine.h"	
#include "Logic/LogicModules/GameLogic/Scene/NewScene.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnitModule.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"	
#include "Logic/ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "protobuf/include/google/protobuf/message.h"	
#include "Logic/ShareCode/Common/EventDispatcher/EventDispacher.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnit(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = int;
				using TypeAlias_2 = google::protobuf::Message *;
				using TypeAlias_3 = void;
				static TypeAlias_3 SendSelf1(GameLogic::SceneUnit &cls, TypeAlias_1 p1, TypeAlias_2 p2)
				{
					return cls.SendSelf(p1, p2);
				}
				using TypeAlias_4 = std::vector<GameLogic::SyncClientMsg, std::allocator<GameLogic::SyncClientMsg> > &;
				using TypeAlias_5 = void;
				static TypeAlias_5 SendSelf2(GameLogic::SceneUnit &cls, TypeAlias_4 p1)
				{
					return cls.SendSelf(p1);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SceneUnit";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnit> meta_table(
						sol::constructors<				
						GameLogic::SceneUnit()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnit"; })				
						,"EnterScene", &GameLogic::SceneUnit::EnterScene				
						,"LeaveScene", &GameLogic::SceneUnit::LeaveScene				
						,"Update", &GameLogic::SceneUnit::Update				
						,"Release", &GameLogic::SceneUnit::Release				
						,"GetScene", &GameLogic::SceneUnit::GetScene				
						,"GetEvDispacher", &GameLogic::SceneUnit::GetEvDispacher				
						,"GetEvProxy", &GameLogic::SceneUnit::GetEvProxy				
						,"GetSceneEvProxy", &GameLogic::SceneUnit::GetSceneEvProxy				
						,"GetTransform", &GameLogic::SceneUnit::GetTransform				
						,"GetId", &GameLogic::SceneUnit::GetId				
						,"GetPlayerId", &GameLogic::SceneUnit::GetPlayerId				
						,"SetPlayerId", &GameLogic::SceneUnit::SetPlayerId				
						,"GetModelId", &GameLogic::SceneUnit::GetModelId				
						,"SetModelId", &GameLogic::SceneUnit::SetModelId				
						,"GetUnitType", &GameLogic::SceneUnit::GetUnitType				
						,"SetUnitType", &GameLogic::SceneUnit::SetUnitType				
						,"GetCamp", &GameLogic::SceneUnit::GetCamp				
						,"SetCamp", &GameLogic::SceneUnit::SetCamp				
						,"CollectPBInit", &GameLogic::SceneUnit::CollectPBInit				
						,"CollectPbMutable", &GameLogic::SceneUnit::CollectPbMutable				
						,"SendSelfEx", &GameLogic::SceneUnit::SendSelfEx				
						,"SendObservers", &GameLogic::SceneUnit::SendObservers				
						,"SendObserversEx", &GameLogic::SceneUnit::SendObserversEx				
						,"ClearPbDirty", &GameLogic::SceneUnit::ClearPbDirty				
						,"SendSelf", sol::overload(ForOverloadFns::SendSelf1, ForOverloadFns::SendSelf2)				
						, sol::base_classes, sol::bases<
							std::enable_shared_from_this<GameLogic::SceneUnit> 
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