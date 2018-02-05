#include "UserType/TryUserTypeUtil.h"
#include <sol.hpp>
#include "try.pb.h"

namespace TryUserType
{
    void LuaBindPB_NetProto_TryItem(lua_State *L)
	{
		struct PBMsg
		{
			static void PBMsg::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
			{
				assert(!name.empty());
				sol::usertype<NetProto::TryItem> meta_table(
					sol::constructors<NetProto::TryItem(), NetProto::TryItem(NetProto::TryItem &)>(),
                        "id", sol::property(&NetProto::TryItem::id, &NetProto::TryItem::set_id),
                        "name", sol::property(&NetProto::TryItem::name, [](NetProto::TryItem &self, std::string v){self.set_name(v);})
				);

				BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
			}
		};

		PBMsg::DoLuaBind(L, "NetProto", "TryItem"); 
	}
}