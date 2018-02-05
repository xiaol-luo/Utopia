#include "ProtobufLuaBind.h"
#include <sol.hpp>
#include "ProtobufLuaBindRepeated.h"
#include "ProtobufLuaBindRepeatedPtr.h"

namespace TryUserType
{
	void LuaBindPBEnum_TryEnum()
	{
		struct PBMsg 
		{
			static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
			{
				assert(!name.empty());
				sol::state_view lua(L);
				sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"a", NetProto::TryEnum::a,
					"b", NetProto::TryEnum::b
				);
			}
		};
		AddLuaBindUserTypeFn([](lua_State *L) {PBMsg::DoLuaBind(L, "NetProto", "TryEnum"); });
	}

	void LuaBindPBEnum_TryNestEnum()
	{
		struct PBMsg
		{
			static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
			{
				assert(!name.empty());
				sol::state_view lua(L);
				sol::table ns_table = GetOrNewLuaNameSpaceTable(lua, name_space);
				{
					sol::optional<sol::object> opt_object = ns_table[name];
					assert(!opt_object);
				}
				ns_table.new_enum(name,
					"a", NetProto::TryMsg_TryNestEnum::TryMsg_TryNestEnum_a,
					"b", NetProto::TryMsg_TryNestEnum::TryMsg_TryNestEnum_b
				);
			}
		};
		AddLuaBindUserTypeFn([](lua_State *L) {PBMsg::DoLuaBind(L, "NetProto.TryMsg", "TryNestEnum"); });
	}

	void LuaBindPB_TryItem()
	{
		struct PBMsg
		{
			static google::protobuf::int32 GetId(NetProto::TryItem &self)
			{
				return self.id();
			}
			static void SetId(NetProto::TryItem &self, google::protobuf::int32 val)
			{
				self.set_id(val);
			}
			static const std::string GetName(NetProto::TryItem &self)
			{
				return self.name();
			}
			static void SetName(NetProto::TryItem &self, const std::string &name)
			{
				self.set_name(name);
			}

			static void PBMsg::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
			{
				assert(!name.empty());
				sol::usertype<NetProto::TryItem> meta_table(
					sol::constructors<NetProto::TryItem(), NetProto::TryItem(NetProto::TryItem &)>(),
					"id", sol::property(PBMsg::GetId, PBMsg::SetId),
					"name", sol::property(PBMsg::GetName, PBMsg::SetName)
				);
				BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
			}
		};

		AddLuaBindUserTypeFn([](lua_State *L) {PBMsg::DoLuaBind(L, "NetProto", "TryItem"); });
	}

	void LuaBindPB_TryMsg()
	{
		struct PBMsg
		{
			static google::protobuf::int32 GetIntVal(NetProto::TryMsg &self)
			{
				return self.int_val();
			}
			static void SetIntVal(NetProto::TryMsg &self, google::protobuf::int32 val)
			{
				self.set_int_val(val);
			}
			static const std::string GetStrVal(NetProto::TryMsg &self)
			{
				return self.str_val();
			}
			static void SetStrVal(NetProto::TryMsg &self, const std::string &name)
			{
				self.set_str_val(name);
			}
			static const NetProto::TryMsg_TryNestEnum GetNestEnumVal(NetProto::TryMsg &self)
			{
				return self.nest_enum_val();
			}
			static void SetNestEnumVal(NetProto::TryMsg &self, NetProto::TryMsg_TryNestEnum val)
			{
				self.set_nest_enum_val(val);
			}
			static google::protobuf::RepeatedField<int>* GetNestEnumArray(NetProto::TryMsg &self)
			{
				return self.mutable_nest_enum_array();
			}
			static ::google::protobuf::RepeatedPtrField< ::NetProto::TryItem >* GetMsgArray(NetProto::TryMsg &self)
			{
				return self.mutable_msg_array();
			}

			static void PBMsg::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
			{
				assert(!name.empty());
				sol::usertype<NetProto::TryMsg> meta_table(
					sol::constructors<NetProto::TryMsg(), NetProto::TryMsg(NetProto::TryMsg &)>(),
					"int_val", sol::property(PBMsg::GetIntVal, PBMsg::SetIntVal),
					"str_val", sol::property(PBMsg::GetStrVal, PBMsg::SetStrVal),
					"nest_enum_val", sol::property(PBMsg::GetNestEnumVal, PBMsg::SetNestEnumVal),
					"nest_enum_array", sol::property(PBMsg::GetNestEnumArray),
					"msg_array", sol::property(PBMsg::GetMsgArray)
					// "nest_enum_array", sol::property([](NetProto::TryMsg &self) {return sol::as_container(self.mutable_nest_enum_array());})
				);
				BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
			}
		};

		AddLuaBindUserTypeFn([](lua_State *L) {PBMsg::DoLuaBind(L, "NetProto", "TryMsg"); });
	}

	void SolLuaBindProtobuf(lua_State *l)
	{
		LuaBindPB_TryItem();
		LuaBindPB_TryMsg(); 
		LuaBindPBEnum_TryEnum();
		LuaBindPBEnum_TryNestEnum();

		AddLuaBindUserTypeFn([](lua_State *L) {PBLuaBindRepeatedField<int>(L, "", "PBLuaBindRepeatedField_int"); });
		AddLuaBindUserTypeFn([](lua_State *L) {PBLuaBindRepeatedField<float>(L, "", "PBLuaBindRepeatedField_float"); });
		AddLuaBindUserTypeFn([](lua_State *L) {PBLuaBindRepeatedField<double>(L, "", "PBLuaBindRepeatedField_double"); });
		AddLuaBindUserTypeFn([](lua_State *L) {PBLuaBindRepeatedField<uint32_t>(L, "", "PBLuaBindRepeatedField_uint32_t"); });
		AddLuaBindUserTypeFn([](lua_State *L) {PBLuaBindRepeatedPtrField<NetProto::TryItem>(L, "", "PBLuaBindRepeatedField_NetProto_TryItem"); });
	}
}
