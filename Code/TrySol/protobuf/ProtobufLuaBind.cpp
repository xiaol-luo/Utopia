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

			static sol::object GetElem(google::protobuf::RepeatedField<int> &self, int idx, sol::this_state l)
			{
				int luaAbsIdx = GetLuaABSIdx(idx, self.size());
				if (luaAbsIdx > self.size())
					return sol::object(l, sol::in_place, sol::lua_nil);
				int val = self.Get(luaAbsIdx - 1);
				return sol::object(l, sol::in_place, val);
			}
			static void SetElem(google::protobuf::RepeatedField<int> &self, int idx, int val)
			{
				int luaAbsIdx = GetLuaABSIdx(idx, self.size());
				if (luaAbsIdx > self.size())
					self.Resize(luaAbsIdx, 0);
				self.Set(luaAbsIdx - 1, val);
			}

			static void EraseRange(google::protobuf::RepeatedField<int> &self, int begin, int end)
			{
				int abs_begin_idx = GetLuaABSIdx(begin, self.size()) - 1;
				int abs_end_idx = GetLuaABSIdx(end, self.size()) - 1;
				self.erase(self.begin() + abs_begin_idx, self.begin() + abs_end_idx);
			}
			static void Erase(google::protobuf::RepeatedField<int> &self, int begin)
			{
				int abs_idx = GetLuaABSIdx(begin, self.size());
				EraseRange(self, abs_idx, abs_idx + 1);
			}
			static int AddEmpty(google::protobuf::RepeatedField<int> &self)
			{
				int val = 0;
				self.Add(val);
				return val;
			}
			static void AddElem(google::protobuf::RepeatedField<int> &self, int val)
			{
				self.Add(val);
			}
			static std::tuple<std::function<std::tuple<sol::object, sol::object>(google::protobuf::RepeatedField<int> &, int, sol::this_state)>, google::protobuf::RepeatedField<int>, int>
				Pairs(google::protobuf::RepeatedField<int> &self)
			{
				auto fn = std::function<std::tuple<sol::object, sol::object>(google::protobuf::RepeatedField<int> &, int, sol::this_state)>(PBBind::Next);
				return std::make_tuple(fn, self, 0);
			}

			static std::tuple<sol::object, sol::object> Next(google::protobuf::RepeatedField<int> &self, int idx, sol::this_state l)
			{
				++idx;
				if (idx > self.size())
					return std::make_tuple(sol::object(sol::lua_nil), sol::object(sol::lua_nil));
				auto v = sol::object(l, sol::in_place, GetElem(self, idx, l));
				return std::make_tuple(sol::object(l, sol::in_place, idx), v);
			}

			static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
			{
				std::string class_name = !name.empty() ? name : "PBLuaBindRepeatedField_int";
				sol::usertype<google::protobuf::RepeatedField<int>> meta_table(
					sol::constructors<
						google::protobuf::RepeatedField<int>(),
						google::protobuf::RepeatedField<int>(google::protobuf::Arena*),
						google::protobuf::RepeatedField<int>(const google::protobuf::RepeatedField<int> &)
					>(), 
					"Get", &google::protobuf::RepeatedField<int>::Get,
					"Mutable", &google::protobuf::RepeatedField<int>::Mutable,
					"Set", &google::protobuf::RepeatedField<int>::Set,
					"Add", sol::overload(
							&PBBind::AddEmpty, 
							&PBBind::AddElem
					),
					"RemoveLast", &google::protobuf::RepeatedField<int>::RemoveLast,
					"Clear", &google::protobuf::RepeatedField<int>::Clear,
					"Reserve", &google::protobuf::RepeatedField<int>::Reserve,
					"Truncate", &google::protobuf::RepeatedField<int>::Truncate,
					"Capacity", &google::protobuf::RepeatedField<int>::Capacity,
					"Resize", &google::protobuf::RepeatedField<int>::Resize,
					"mutable_data", &google::protobuf::RepeatedField<int>::mutable_data,
					"data", &google::protobuf::RepeatedField<int>::data,
					"Swap", &google::protobuf::RepeatedField<int>::Swap,
					"SwapElements", &google::protobuf::RepeatedField<int>::SwapElements,
					"erase", sol::overload(
						&PBBind::Erase,
						&PBBind::EraseRange
					),
					sol::meta_function::pairs, &PBBind::Pairs,
					sol::meta_function::length, &google::protobuf::RepeatedField<int>::size
					// sol::meta_function::next, &PBBind::Next
					// sol::meta_function::index, &PBBind::GetElem,
					// sol::meta_function::new_index, &PBBind::SetElem,
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
