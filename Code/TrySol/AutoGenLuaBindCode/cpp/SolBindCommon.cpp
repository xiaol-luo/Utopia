#include <sol.hpp>

namespace SolLuaBind 
{
        extern void LuaBind_(lua_State *L);
        extern void LuaBind_NoneSpaceClass(lua_State *L);
        extern void LuaBind_TryEnum(lua_State *L);
        extern void LuaBind_OK(lua_State *L);
        extern void LuaBind_OK(lua_State *L);
        extern void LuaBind_OK_Test(lua_State *L);
        extern void LuaBind_OK_Base(lua_State *L);
        extern void LuaBind_OK_OuterClass(lua_State *L);
        extern void LuaBind_OK_Test(lua_State *L);
        extern void LuaBind_OK_Base(lua_State *L);
        extern void LuaBind_OK_OuterClass(lua_State *L);
        extern void LuaBind_OK_OuterClass_InnerClass(lua_State *L);
        extern void LuaBind_OK_OuterClass_InnerClass(lua_State *L);

	void SolLuaBind(lua_State *L)
	{
            LuaBind_(L);
            LuaBind_NoneSpaceClass(L);
            LuaBind_TryEnum(L);
            LuaBind_OK(L);
            LuaBind_OK(L);
            LuaBind_OK_Test(L);
            LuaBind_OK_Base(L);
            LuaBind_OK_OuterClass(L);
            LuaBind_OK_Test(L);
            LuaBind_OK_Base(L);
            LuaBind_OK_OuterClass(L);
            LuaBind_OK_OuterClass_InnerClass(L);
            LuaBind_OK_OuterClass_InnerClass(L);
	}
}