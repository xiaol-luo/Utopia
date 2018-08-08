config_base = {}

function config_base.load(cfg_path) 
end

function  cfg_abs_path(cfg_path)
    local ret = CS.Lua.LuaHelp.GetCfgAbsPath(cfg_path)
    return ret
end
