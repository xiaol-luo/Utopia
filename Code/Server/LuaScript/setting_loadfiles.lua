
_load_files_load_files_init =
{
	"LuaScript/init.lua",
}

_load_files_libs = {
    "LuaScript/libs/common/class.lua",
    "LuaScript/libs/lua_protobuf/protoc.lua",
    "LuaScript/libs/lua_protobuf/serpent.lua",
    "LuaScript/libs/net/net.lua",
}

_load_files_logic_net_handler = {
    "LuaScript/logic/net/parse_protobuf.lua",
    "LuaScript/logic/net/net_handler.lua",
    "LuaScript/logic/net/msg_handlers.lua",
}

 _load_files_effect_script = {
    "LuaScript/logic/effects/init.lua",
    "LuaScript/logic/effects/effect_base.lua",
    "LuaScript/logic/effects/effect_demo.lua",
}

_load_files_map =
{
    _load_files_load_files_init,
    _load_files_libs,
    _load_files_logic_net_handler,
    _load_files_effect_script,
}


