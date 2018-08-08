

STRING_TYPE_NAME = type("")
TABLE_TYPE_NAME = type({})

function load_files(val)
    local type_name = type(val)
    if STRING_TYPE_NAME == type_name then 
        print(string.format("load file %s", val))
        local abs_path = CS.Lua.LuaHelp.GetLuaAbsPath(val)
        local fn, err_msg = loadfile(abs_path)
        if nil ~= fn then 
            fn()
        else
            print(string.format("load file %s:%s fail, reason : %s", val, abs_path, err_msg))
        end
        return
    end
    
    if TABLE_TYPE_NAME == type_name then 
        for k, v in pairs(val) do
            load_files(v)
        end
    end
end

function reload_files(tb_name)
    print(string.format("reload_files start %s", tb_name))

    load_files("global_def.lua")
    load_files("setting_loadfiles.lua")
    tb_name = tb_name or "_load_files_map"
    local t = _G[tb_name]
    if nil == t then
        print(string.format("reload_filesis nil  %s ", tb_name))
    else
        load_files(t)
        print(string.format("reload_files end %s", tb_name))
    end
end

reload_files()

