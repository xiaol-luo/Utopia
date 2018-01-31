#include "ProtobufLuaBind.h"
#include <sol.hpp>

namespace TryUserType
{
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
				std::string class_name = !name.empty() ? name : "TryItem";
				sol::usertype<NetProto::TryItem> meta_table(
					sol::constructors<NetProto::TryItem(), NetProto::TryItem(NetProto::TryItem &)>(),
					"id", sol::property(PBMsg::GetId, PBMsg::SetId),
					"name", sol::property(PBMsg::GetName, PBMsg::SetName)
				);
				BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
			}
		};

		AddLuaBindUserTypeFn([](lua_State *L) {PBMsg::DoLuaBind(L, "NetProto", ""); });
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

			static void PBMsg::DoLuaBind(lua_State * L, const std::string & name_space, const std::string & name)
			{
				std::string class_name = !name.empty() ? name : "TryMsg";
				sol::usertype<NetProto::TryMsg> meta_table(
					sol::constructors<NetProto::TryMsg(), NetProto::TryMsg(NetProto::TryMsg &)>(),
					"int_val", sol::property(PBMsg::GetIntVal, PBMsg::SetIntVal),
					"str_val", sol::property(PBMsg::GetStrVal, PBMsg::SetStrVal),
					"nest_enum_val", sol::property(PBMsg::GetNestEnumVal, PBMsg::SetNestEnumVal),
					"nest_enum_array", sol::property(PBMsg::GetNestEnumArray)
					// "nest_enum_array", sol::property([](NetProto::TryMsg &self) {return sol::as_container(self.mutable_nest_enum_array());})
				);
				BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
			}
		};

		AddLuaBindUserTypeFn([](lua_State *L) {PBMsg::DoLuaBind(L, "NetProto", ""); });
	}

	void PBLuaBindRepeatedFieldSet(google::protobuf::RepeatedField<int> &self, int idx, int val)
	{
		assert(idx >= 0);
		if (idx >= self.size())
		{
			self.Resize(idx + 1, 0);
		}
		self.Set(idx, val);
	}
	int PBLuaBindRepeatedFieldGet(google::protobuf::RepeatedField<int> &self, int idx)
	{
		assert(idx >= 0);
		if (idx >= self.size())
			return 0;
		return self.Get(idx);
	}
	void PBLuaBindRepeatedField_int(lua_State *L, const std::string &name_space, const std::string &name)
	{
		struct PBBind
		{
			static int GetLuaABSIdx(int idx, int len)
			{
				int ret = idx;
				assert(0 != idx);
				if (idx < 0)
					ret = len + idx + 1;
				if (ret <= 0)
					ret = 1;
				return ret;
			}

			static sol::optional<int> GetElem(google::protobuf::RepeatedField<int> &self, int idx)
			{
				int luaAbsIdx = GetLuaABSIdx(idx, self.size());
				if (luaAbsIdx > self.size())
					return 0;
				return self.Get(luaAbsIdx - 1);
			}
			static void SetElem(google::protobuf::RepeatedField<int> &self, int idx, int val)
			{
				int luaAbsIdx = GetLuaABSIdx(idx, self.size());
				if (luaAbsIdx > self.size())
					self.Resize(luaAbsIdx, 0);
				self.Set(luaAbsIdx - 1, val);
			}

			static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
			{
				std::string class_name = !name.empty() ? name : "PBLuaBindRepeatedField_int";
				sol::usertype<google::protobuf::RepeatedField<int>> meta_table(
					sol::constructors<google::protobuf::RepeatedField<int>(),
					google::protobuf::RepeatedField<int>(const google::protobuf::RepeatedField<int> &)>(), 
					sol::meta_function::index, &PBBind::GetElem,
					sol::meta_function::new_index, &PBBind::SetElem,
					sol::meta_function::length, &google::protobuf::RepeatedField<int>::size
				);
				BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
			}
		};

		PBBind::DoLuaBind(L, name_space, name);
	}

	void RegisterProtobuf(lua_State *l)
	{
		LuaBindPB_TryMsg();
		AddLuaBindUserTypeFn([](lua_State *L) {PBLuaBindRepeatedField_int(L, "", ""); });
		AddLuaBindUserTypeFn([](lua_State *L) {DoLuaBind<NetProto::TryEnum>(L, "NetProto", ""); });
		AddLuaBindUserTypeFn([](lua_State *L) {DoLuaBind<NetProto::TryMsg_TryNestEnum>(L, "NetProto.TryMsg", ""); });
	}
}
