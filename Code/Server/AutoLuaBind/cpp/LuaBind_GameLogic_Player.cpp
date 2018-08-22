#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "protobuf/include/google/protobuf/message.h"	
#include "LogicModules/GameLogic/Player/PlayerMgr.h"	
#include "CommonModules/Network/INetworkHandler.h"	
#include "LogicModules/GameLogic/Player/Player.h"	
#include "LogicModules/GameLogic/Scene/NewScene.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "LogicModules/GameLogic/GameLogicModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_Player(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = int;
				using TypeAlias_2 = char *;
				using TypeAlias_3 = unsigned int;
				using TypeAlias_4 = void;
				static TypeAlias_4 Send1(GameLogic::Player &cls, TypeAlias_1 p1, TypeAlias_2 p2, TypeAlias_3 p3)
				{
					return cls.Send(p1, p2, p3);
				}
				using TypeAlias_5 = int;
				using TypeAlias_6 = google::protobuf::Message *;
				using TypeAlias_7 = void;
				static TypeAlias_7 Send2(GameLogic::Player &cls, TypeAlias_5 p1, TypeAlias_6 p2)
				{
					return cls.Send(p1, p2);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Player";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::Player> meta_table(
						sol::constructors<				
						GameLogic::Player(GameLogic::PlayerMgr *, uint64_t)
						>(),
						"__StructName__", sol::property([]() {return "Player"; })				
						,"operator new", &GameLogic::Player::operator new				
						,"operator delete", &GameLogic::Player::operator delete				
						,"operator new[]", &GameLogic::Player::operator new[]				
						,"operator delete[]", &GameLogic::Player::operator delete[]				
						,"GetCnnHandler", &GameLogic::Player::GetCnnHandler				
						,"GetNetId", &GameLogic::Player::GetNetId				
						,"SendMsg", &GameLogic::Player::SendMsg				
						,"Close", &GameLogic::Player::Close				
						,"GetSu", &GameLogic::Player::GetSu				
						,"SetSu", &GameLogic::Player::SetSu				
						,"GetScene", &GameLogic::Player::GetScene				
						,"SetScene", &GameLogic::Player::SetScene				
						,"Send", sol::overload(ForOverloadFns::Send1, ForOverloadFns::Send2)
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