

_load_files_libs = {
    "LuaScript/libs/common/class.lua",
    "LuaScript/libs/lua_protobuf/protoc.lua",
    "LuaScript/libs/lua_protobuf/serpent.lua",
    "LuaScript/libs/net/net.lua",
    "LuaScript/libs/lua_rapidjson/rapidjson.lua",
}

_load_configs = {
    "LuaScript/logic/configs/init.lua",
    "LuaScript/logic/configs/load_json_config.lua",
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
    _load_files_libs,
    _load_configs,
    _load_files_logic_net_handler,
    _load_files_effect_script,
}


