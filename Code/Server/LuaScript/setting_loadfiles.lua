
_load_files_init =
{
	"LuaScript/init.lua",
    "LuaScript/MainTest.lua",
	"LuaScript/HoldPlace.lua"
}

local _lib_lua_protobuf = {
    "LuaScript/libs/lua_protobuf/protoc.lua",
    "LuaScript/libs/lua_protobuf/serpent.lua",
    "LuaScript/HoldPlace.lua"
}

local _lib_net = {
    "LuaScript/libs/net/net.lua",
    "LuaScript/HoldPlace.lua"
}

local _lib_common = {
    "LuaScript/libs/common/class.lua",
    "LuaScript/HoldPlace.lua"
}

_load_files_effect_script = {
    "LuaScript/effect_script/init.lua",
    "LuaScript/effect_script/effect_script_base.lua",
    "LuaScript/effect_script/effect_script_demo.lua",
    "LuaScript/HoldPlace.lua"
}

local _logic_net_handler = {
    "LuaScript/logic/net_handler.lua",
}

_load_files_map =
{
    _lib_common,
    _lib_lua_protobuf,
    _lib_net,
    _load_files_init,
    _load_files_effect_script,
    _logic_net_handler,
}


