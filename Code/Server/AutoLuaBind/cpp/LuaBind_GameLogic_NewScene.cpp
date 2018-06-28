#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/NewScene.h"	
#include "GameLogic/Scene/Config/SceneAllConfig.h"	
#include "protobuf/include/google/protobuf/arena.h"	
#include "GameLogic/Scene/SceneModule/SceneModule.h"	
#include "Common/EventDispatcher/EventDispacher.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Config/AutoCsvCode/Scene/CsvSceneConfig.h"	
#include "GameLogic/Player/Player.h"	
#include "protobuf/include/google/protobuf/message.h"	
#include "GameLogic/GameLogicModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_NewScene(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = unsigned long long;
				using TypeAlias_2 = int;
				using TypeAlias_3 = google::protobuf::Message *;
				using TypeAlias_4 = void;
				static TypeAlias_4 SendPlayer1(GameLogic::NewScene &cls, TypeAlias_1 p1, TypeAlias_2 p2, TypeAlias_3 p3)
				{
					return cls.SendPlayer(p1, p2, p3);
				}
				using TypeAlias_5 = unsigned long long;
				using TypeAlias_6 = const std::vector<GameLogic::SyncClientMsg, std::allocator<GameLogic::SyncClientMsg> > &;
				using TypeAlias_7 = void;
				static TypeAlias_7 SendPlayer2(GameLogic::NewScene &cls, TypeAlias_5 p1, TypeAlias_6 p2)
				{
					return cls.SendPlayer(p1, p2);
				}
				using TypeAlias_8 = long long;
				using TypeAlias_9 = int;
				using TypeAlias_10 = google::protobuf::Message *;
				using TypeAlias_11 = void;
				static TypeAlias_11 SendObservers1(GameLogic::NewScene &cls, TypeAlias_8 p1, TypeAlias_9 p2, TypeAlias_10 p3)
				{
					return cls.SendObservers(p1, p2, p3);
				}
				using TypeAlias_12 = long long;
				using TypeAlias_13 = const std::vector<GameLogic::SyncClientMsg, std::allocator<GameLogic::SyncClientMsg> > &;
				using TypeAlias_14 = void;
				static TypeAlias_14 SendObservers2(GameLogic::NewScene &cls, TypeAlias_12 p1, TypeAlias_13 p2)
				{
					return cls.SendObservers(p1, p2);
				}
				using TypeAlias_15 = GameLogic::EViewCamp;
				using TypeAlias_16 = int;
				using TypeAlias_17 = google::protobuf::Message *;
				using TypeAlias_18 = bool;
				using TypeAlias_19 = void;
				static TypeAlias_19 SendViewCamp1(GameLogic::NewScene &cls, TypeAlias_15 p1, TypeAlias_16 p2, TypeAlias_17 p3, TypeAlias_18 p4)
				{
					return cls.SendViewCamp(p1, p2, p3, p4);
				}
				using TypeAlias_20 = GameLogic::EViewCamp;
				using TypeAlias_21 = const std::vector<GameLogic::SyncClientMsg, std::allocator<GameLogic::SyncClientMsg> > &;
				using TypeAlias_22 = bool;
				using TypeAlias_23 = void;
				static TypeAlias_23 SendViewCamp2(GameLogic::NewScene &cls, TypeAlias_20 p1, TypeAlias_21 p2, TypeAlias_22 p3)
				{
					return cls.SendViewCamp(p1, p2, p3);
				}
				using TypeAlias_24 = std::shared_ptr<GameLogic::SceneUnit>;
				using TypeAlias_25 = std::shared_ptr<GameLogic::SceneUnit>;
				using TypeAlias_26 = NetProto::ESceneUnitRelation;
				static TypeAlias_26 SceneUnitRelation1(GameLogic::NewScene &cls, TypeAlias_24 p1, TypeAlias_25 p2)
				{
					return cls.SceneUnitRelation(p1, p2);
				}
				using TypeAlias_27 = GameLogic::SceneUnit *;
				using TypeAlias_28 = GameLogic::SceneUnit *;
				using TypeAlias_29 = NetProto::ESceneUnitRelation;
				static TypeAlias_29 SceneUnitRelation2(GameLogic::NewScene &cls, TypeAlias_27 p1, TypeAlias_28 p2)
				{
					return cls.SceneUnitRelation(p1, p2);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "NewScene";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::NewScene> meta_table(
						sol::constructors<				
						GameLogic::NewScene(GameLogicModule *)
						>(),
						"__StructName__", sol::property([]() {return "NewScene"; })				
						,"m_player_view_camps", &GameLogic::NewScene::m_player_view_camps				
						,"red_su", &GameLogic::NewScene::red_su				
						,"blue_su", &GameLogic::NewScene::blue_su				
						,"AddModule", &GameLogic::NewScene::AddModule				
						,"Awake", &GameLogic::NewScene::Awake				
						,"Update", &GameLogic::NewScene::Update				
						,"Destroy", &GameLogic::NewScene::Destroy				
						,"GetLogicSec", &GameLogic::NewScene::GetLogicSec				
						,"GetLogicMs", &GameLogic::NewScene::GetLogicMs				
						,"GetLogicDetalMs", &GameLogic::NewScene::GetLogicDetalMs				
						,"GetEvDispacher", &GameLogic::NewScene::GetEvDispacher				
						,"GetGameLogic", &GameLogic::NewScene::GetGameLogic				
						,"GetCfg", &GameLogic::NewScene::GetCfg				
						,"AddUnit", &GameLogic::NewScene::AddUnit				
						,"RemoveUnit", &GameLogic::NewScene::RemoveUnit				
						,"GetUnit", &GameLogic::NewScene::GetUnit				
						,"ForeachSceneUnit", &GameLogic::NewScene::ForeachSceneUnit				
						,"PlayerSelectHero", &GameLogic::NewScene::PlayerSelectHero				
						,"OnPlayerDisconnect", &GameLogic::NewScene::OnPlayerDisconnect				
						,"OnPlayerQuit", &GameLogic::NewScene::OnPlayerQuit				
						,"SetPlayerViewCamp", &GameLogic::NewScene::SetPlayerViewCamp				
						,"MakeSnapshot", &GameLogic::NewScene::MakeSnapshot				
						,"SendPlayer", sol::overload(ForOverloadFns::SendPlayer1, ForOverloadFns::SendPlayer2)				
						,"SendObservers", sol::overload(ForOverloadFns::SendObservers1, ForOverloadFns::SendObservers2)				
						,"SendViewCamp", sol::overload(ForOverloadFns::SendViewCamp1, ForOverloadFns::SendViewCamp2)				
						,"SceneUnitRelation", sol::overload(ForOverloadFns::SceneUnitRelation1, ForOverloadFns::SceneUnitRelation2)
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