#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/CommonModules/Network/INetworkHandler.h"	
#include "Logic/LogicModules/GameLogic/Player/PlayerMgr.h"	
#include "Logic/LogicModules/GameLogic/Player/Player.h"	
#include "Libs/3rdpartLibs/protobuf/include/google/protobuf/message.h"	
#include "Logic/LogicModules/GameLogic/GameLogicModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_PlayerMgr(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = unsigned long long;
				using TypeAlias_2 = int;
				using TypeAlias_3 = char *;
				using TypeAlias_4 = unsigned int;
				using TypeAlias_5 = void;
				static TypeAlias_5 Send1(GameLogic::PlayerMgr &cls, TypeAlias_1 p1, TypeAlias_2 p2, TypeAlias_3 p3, TypeAlias_4 p4)
				{
					return cls.Send(p1, p2, p3, p4);
				}
				using TypeAlias_6 = unsigned long long;
				using TypeAlias_7 = int;
				using TypeAlias_8 = google::protobuf::Message *;
				using TypeAlias_9 = void;
				static TypeAlias_9 Send2(GameLogic::PlayerMgr &cls, TypeAlias_6 p1, TypeAlias_7 p2, TypeAlias_8 p3)
				{
					return cls.Send(p1, p2, p3);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "PlayerMgr";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::PlayerMgr> meta_table(
						sol::constructors<				
						GameLogic::PlayerMgr(GameLogicModule *)
						>(),
						"__StructName__", sol::property([]() {return "PlayerMgr"; })				
						,"operator new", &GameLogic::PlayerMgr::operator new				
						,"operator delete", &GameLogic::PlayerMgr::operator delete				
						,"operator new[]", &GameLogic::PlayerMgr::operator new[]				
						,"operator delete[]", &GameLogic::PlayerMgr::operator delete[]				
						,"Awake", &GameLogic::PlayerMgr::Awake				
						,"Update", &GameLogic::PlayerMgr::Update				
						,"OnCnnClose", &GameLogic::PlayerMgr::OnCnnClose				
						,"OnCnnRecv", &GameLogic::PlayerMgr::OnCnnRecv				
						,"OnCnnOpen", &GameLogic::PlayerMgr::OnCnnOpen				
						,"RemovePlayer", &GameLogic::PlayerMgr::RemovePlayer				
						,"Close", &GameLogic::PlayerMgr::Close				
						,"Send", sol::overload(ForOverloadFns::Send1, ForOverloadFns::Send2)
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "BROADCAST_NETID";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::PlayerMgr::BROADCAST_NETID);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}