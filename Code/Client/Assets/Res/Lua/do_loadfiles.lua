
function load_files(t)
    local type_name = type(t)
    if g_def.type_name.string == type_name then 
        print(string.format("load file %s", t))
        CS.Lua.LuaHelp.LoadLuaFile(t)
        return
    end
    
    if g_def.type_name.table == type_name then 
        for k, v in pairs(t) do
            load_files(v)
        end
    end
end

function reload_files(tb_name)
    local t = _G[tb_name]
    print(tb_name)
    print(t)
    print("reload_files here 2")
    if nil == t then
        print(string.format("%s is nil", tb_name))
    else
        load_files(t)
        print(string.format("%s reload succ", tb_name))
    end
end

load_files(_load_files_map)

