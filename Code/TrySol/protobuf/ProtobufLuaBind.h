#include "try.pb.h"
#include "UserType/TryUserTypeUtil.h"

namespace TryUserType {

	template <>
	static void TryUserType::DoLuaBind<NetProto::TryEnum>(lua_State *L, const std::string &name_space, const std::string &name)
	{
		std::string enum_name = !name.empty() ? name : "TryEnum";
		sol::state_view lua(L);
		sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
		{
			sol::optional<sol::object> opt_object = ns_table[enum_name];
			assert(!opt_object);
		}
		ns_table.new_enum(enum_name,
			"a", NetProto::TryEnum::a,
			"b", NetProto::TryEnum::b
		);
	}

	template <>
	static void TryUserType::DoLuaBind<NetProto::TryMsg_TryNestEnum>(lua_State *L, const std::string &name_space, const std::string &name)
	{
		std::string enum_name = !name.empty() ? name : "TryNestEnum";
		sol::state_view lua(L);
		sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
		{
			sol::optional<sol::object> opt_object = ns_table[enum_name];
			assert(!opt_object);
		}
		ns_table.new_enum(enum_name,
			"a", NetProto::TryMsg_TryNestEnum::TryMsg_TryNestEnum_a,
			"b", NetProto::TryMsg_TryNestEnum::TryMsg_TryNestEnum_b
		);
	}
	void RegisterProtobuf(lua_State *l);
	void LuaBindPB_TryItem();
	void LuaBindPB_TryMsg();
}

namespace sol {
	template<>
	struct is_container<google::protobuf::RepeatedField<int>> : std::false_type {};
}

