#include <sol.hpp>
#include "protobuf/ProtobufLuaBindRepeated.h"
#include "protobuf/ProtobufLuaBindRepeatedPtr.h"
#include "try.pb.h"

namespace TryUserType 
{
	extern void LuaBindPB_NetProto_TryEnum(lua_State *L);
	extern void LuaBindPB_NetProto_TryItem(lua_State *L);
	extern void LuaBindPB_NetProto_TryMsg(lua_State *L);
	extern void LuaBindPB_NetProto_TryMsg_TryNestEnum(lua_State *L);
	extern void LuaBind_TryEnum(lua_State *L);
	extern void LuaBind_OK(lua_State *L);
	extern void LuaBind_OK_OuterClass(lua_State *L);

	void SolLuaBindProtobuf(lua_State *L)
	{
		PBLuaBindRepeatedField<double>(L, "google_protobuf_double", "Test");
		PBLuaBindRepeatedField<double>(L, "", "google_protobuf_double");
		PBLuaBindRepeatedField<float>(L, "", "google_protobuf_float");
		PBLuaBindRepeatedField<google::protobuf::int32>(L, "", "google_protobuf_int32");
		PBLuaBindRepeatedField<google::protobuf::int64>(L, "", "google_protobuf_int64");
		PBLuaBindRepeatedField<google::protobuf::uint32>(L, "", "google_protobuf_uint32");
		PBLuaBindRepeatedField<google::protobuf::uint64>(L, "", "google_protobuf_uint64");
		PBLuaBindRepeatedField<bool>(L, "", "google_protobuf_bool");
		PBLuaBindRepeatedField<google::protobuf::string>(L, "", "google_protobuf_string");
		PBLuaBindRepeatedField<unsigned char>(L, "", "google_protobuf_uchar");
		PBLuaBindRepeatedField<char>(L, "", "google_protobuf_char");
		PBLuaBindRepeatedPtrField<std::string>(L, "", "google_protobuf_string");
		LuaBindPB_NetProto_TryEnum(L);
		LuaBindPB_NetProto_TryItem(L);
		LuaBindPB_NetProto_TryMsg(L);
		LuaBindPB_NetProto_TryMsg_TryNestEnum(L);
		PBLuaBindRepeatedPtrField<NetProto::TryItem>(L, "", "NetProto_TryItem");
		PBLuaBindRepeatedPtrField<NetProto::TryMsg>(L, "", "NetProto_TryMsg");

		LuaBind_TryEnum(L);
		LuaBind_OK(L);
		LuaBind_OK_OuterClass(L);
	}
}