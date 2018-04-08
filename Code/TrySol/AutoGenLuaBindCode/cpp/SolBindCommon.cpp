#include <sol.hpp>

namespace SolLuaBind 
{
        extern void LuaBind_(lua_State *L);
        extern void LuaBind_Vector3(lua_State *L);
        extern void LuaBind_Vector2(lua_State *L);
        extern void LuaBind_GeometryUtils(lua_State *L);

	void SolLuaBind(lua_State *L)
	{
            LuaBind_(L);
            LuaBind_Vector3(L);
            LuaBind_Vector2(L);
            LuaBind_GeometryUtils(L);
	}
}