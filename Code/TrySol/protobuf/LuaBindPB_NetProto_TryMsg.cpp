#include "UserType/TryUserTypeUtil.h"
#include <sol.hpp>
#include "try.pb.h"

namespace TryUserType
{
    void LuaBindPB_NetProto_TryMsg(lua_State *L)
	{
		struct PBMsg
		{
			static void PBMsg::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
			{
				assert(!name.empty());
				sol::usertype<NetProto::TryMsg> meta_table(
					sol::constructors<NetProto::TryMsg(), NetProto::TryMsg(NetProto::TryMsg &)>(),
                        "int_val", sol::property(&NetProto::TryMsg::int_val, &NetProto::TryMsg::set_int_val),
                        "str_val", sol::property(&NetProto::TryMsg::str_val, [](NetProto::TryMsg &self, std::string v){self.set_str_val(v);}),
                        "msg_val", sol::property([](NetProto::TryMsg &self) { return self.mutable_msg_val(); }),
                        "enum_val", sol::property(&NetProto::TryMsg::enum_val, &NetProto::TryMsg::set_enum_val),
                        "nest_enum_val", sol::property(&NetProto::TryMsg::nest_enum_val, &NetProto::TryMsg::set_nest_enum_val),
                        "msg_array", sol::property([](NetProto::TryMsg &self) { return self.mutable_msg_array(); }),
                        "nest_enum_array", sol::property([](NetProto::TryMsg &self) { return self.mutable_nest_enum_array(); })
				);

				BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
			}
		};

		PBMsg::DoLuaBind(L, "NetProto", "TryMsg"); 
	}
}