#include <sol.hpp>
#include <google/protobuf/repeated_field.h>
#include "UserType/TryUserTypeUtil.h"

template <typename T>
void PBLuaBindRepeatedPtrField(lua_State *L, const std::string &name_space, const std::string &name)
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

		static sol::object GetElem(google::protobuf::RepeatedPtrField<T> &self, int idx, sol::this_state l)
		{
			int luaAbsIdx = GetLuaABSIdx(idx, self.size());
			if (luaAbsIdx > self.size())
				return sol::object(l, sol::in_place, sol::lua_nil);
			auto val = self.Mutable(luaAbsIdx - 1);
			return sol::object(l, sol::in_place, val);
		}
		static void SetElem(google::protobuf::RepeatedPtrField<T>&self, int idx, T *val)
		{
			int luaAbsIdx = GetLuaABSIdx(idx, self.size());
			T *elem = self.Mutable(luaAbsIdx - 1);
			*elem = *val;
		}
		static void EraseRange(google::protobuf::RepeatedPtrField<T>&self, int begin, int end)
		{
			int abs_begin_idx = GetLuaABSIdx(begin, self.size()) - 1;
			int abs_end_idx = GetLuaABSIdx(end, self.size()) - 1;
			if (abs_begin_idx > self.size() || abs_begin_idx >= abs_end_idx)
				return;
			self.erase(self.begin() + abs_begin_idx, self.begin() + abs_end_idx);
		}
		static void Erase(google::protobuf::RepeatedPtrField<T>&self, int begin)
		{
			int abs_idx = GetLuaABSIdx(begin, self.size());
			EraseRange(self, abs_idx, abs_idx + 1);
		}
		static sol::object AddEmpty(google::protobuf::RepeatedPtrField<T>&self, sol::this_state l)
		{
			self.Add();
			// self.Add(std::move(T()));
			return GetElem(self, -1, l);
		}
		static sol::object AddElem(google::protobuf::RepeatedPtrField<T>&self, T &val, sol::this_state l)
		{
			T *elem = self.Add();
			*elem = val;
			return GetElem(self, -1, l);
		}
		typedef std::tuple<sol::object, sol::object> (*NextFnDef)(google::protobuf::RepeatedPtrField<T>&, int, sol::this_state);
		// static std::tuple<std::function<std::tuple<sol::object, sol::object>(google::protobuf::RepeatedPtrField<T>&, int, sol::this_state)>, google::protobuf::RepeatedPtrField<T>, int>
		static std::tuple<NextFnDef, google::protobuf::RepeatedPtrField<T>, int>
		Pairs(google::protobuf::RepeatedPtrField<T>&self)
		{
			// auto fn = std::function<std::tuple<sol::object, sol::object>(google::protobuf::RepeatedPtrField<T>&, int, sol::this_state)>(PBBind::Next);
			auto fn = &PBBind::Next;
			return std::make_tuple(fn, self, 0);
		}

		static std::tuple<sol::object, sol::object> Next(google::protobuf::RepeatedPtrField<T>&self, int idx, sol::this_state l)
		{
			++idx;
			if (idx > self.size())
				return std::make_tuple(sol::object(sol::lua_nil), sol::object(sol::lua_nil));
			auto v = sol::object(l, sol::in_place, GetElem(self, idx, l));
			return std::make_tuple(sol::object(l, sol::in_place, idx), v);
		}
		static std::vector<T *> GetData(google::protobuf::RepeatedPtrField<T>&self, sol::this_state l)
		{
			if (self.size() > 0)
				return std::move(std::vector<T *>(self.mutable_data(), self.mutable_data() + self.size()));
			return std::move(std::vector<T *>());
		}

		static void DoLuaBind(lua_State *L, const std::string &name_space, const std::string &name)
		{
			assert(!name.empty());
			std::string class_name = name;
			sol::usertype<google::protobuf::RepeatedPtrField<T>> meta_table(
				sol::constructors<
				google::protobuf::RepeatedPtrField<T>(),
				google::protobuf::RepeatedPtrField<T>(google::protobuf::Arena*),
				google::protobuf::RepeatedPtrField<T>(const google::protobuf::RepeatedPtrField<T>&)
				>(),
				"Get", &PBBind::GetElem,
				"Set", &PBBind::SetElem,
				"Mutable", &google::protobuf::RepeatedPtrField<T>::Mutable,
				"Add", sol::overload(
					&PBBind::AddEmpty,
					&PBBind::AddElem
				),
				"RemoveLast", &google::protobuf::RepeatedPtrField<T>::RemoveLast,
				"Clear", &google::protobuf::RepeatedPtrField<T>::Clear,
				"Capacity", &google::protobuf::RepeatedPtrField<T>::Capacity,
				"Data", &PBBind::GetData,
				"Swap", &google::protobuf::RepeatedPtrField<T>::Swap,
				"SwapElements", &google::protobuf::RepeatedPtrField<T>::SwapElements,
				"Erase", sol::overload(
					&PBBind::Erase,
					&PBBind::EraseRange
				),
				sol::meta_function::pairs, &PBBind::Pairs,
				sol::meta_function::index, &PBBind::GetElem,
				sol::meta_function::new_index, &PBBind::SetElem
			);
			TryUserType::BindLuaUserType(sol::state_view(L), meta_table, class_name, name_space);
		}
	};

	PBBind::DoLuaBind(L, name_space, name);
}