
_load_files_init =
{
	"LuaScript/init.lua",
    "LuaScript/class.lua",
    "LuaScript/MainTest.lua",
	"LuaScript/HoldPlace.lua"
}

local _lib_lua_protobuf = {
    "LuaScript/libs/lua_protobuf/protoc.lua",
    "LuaScript/libs/lua_protobuf/serpent.lua",
    "LuaScript/HoldPlace.lua"
}

_load_files_effect_script =
{
    "LuaScript/effect_script/init.lua",
    "LuaScript/effect_script/effect_script_base.lua",
    "LuaScript/effect_script/effect_script_demo.lua",
    "LuaScript/HoldPlace.lua"
}

_load_files_map =
{
    _lib_lua_protobuf,
    _load_files_init,
    _load_files_effect_script,
}


