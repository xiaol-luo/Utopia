#include "try.pb.h"
#include "UserType/TryUserTypeUtil.h"

namespace TryUserType {
	void RegisterProtobuf(lua_State *l);
	void LuaBindPB_TryItem();
	void LuaBindPB_TryMsg();
}

