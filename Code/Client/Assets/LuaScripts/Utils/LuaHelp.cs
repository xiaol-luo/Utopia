
using System.IO;
using UnityEngine;
using Utopia;
using XLua;

namespace Lua
{
    [LuaCallCSharp]
    public partial class LuaHelp
    {
        public static string GetLuaAbsPath(string filePath)
        {
            string luaRootDir = Path.Combine(Application.dataPath, "Res/Lua");
            string luaFile = Path.Combine(luaRootDir, filePath);
            return luaFile.Replace('\\', '/');
        }

        public static string GetCfgAbsPath(string cfgPath)
        {
            string cfgRootDir = Path.Combine(Application.dataPath, "Res/Config");
            string luaFile = Path.Combine(cfgRootDir, cfgPath);
            return luaFile.Replace('\\', '/');
        }

        public static void ReloadScripts(string scriptTable)
        {
            LuaFunction loadFiles = App.instance.lua.Global.Get<LuaFunction>("reload_files");
            loadFiles.Call(scriptTable);
        }
    }
}