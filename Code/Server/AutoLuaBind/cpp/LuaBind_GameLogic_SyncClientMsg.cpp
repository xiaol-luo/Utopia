#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "protobuf/include/google/protobuf/message.h"	
#include "GameLogic/Scene/Defines/SceneDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SyncClientMsg(lua_State *L)
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
                std::string name = "SyncClientMsg";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SyncClientMsg> meta_table(
						sol::constructors<				
						GameLogic::SyncClientMsg(int, google::protobuf::Message *)
						>(),
						"__StructName__", sol::property([]() {return "SyncClientMsg"; })				
						,"protocol_id", &GameLogic::SyncClientMsg::protocol_id				
						,"msg", &GameLogic::SyncClientMsg::msg
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