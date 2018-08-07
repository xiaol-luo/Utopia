
function load_files(t)
    for k, v in pairs(t) do
        print(v)
        type_name = type(v)
        if g_def.type_name.string == type_name then 
            CS.Lua.LuaHelp.LoadLuaFile(v)
        end

        if g_def.type_name.table == type_name then 
            load_files(v)
        end
    end
end

load_files(_load_files_map)

