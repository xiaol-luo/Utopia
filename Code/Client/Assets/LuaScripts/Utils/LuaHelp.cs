
using Utopia;
using XLua;

namespace Lua
{
    [LuaCallCSharp]
    public partial class LuaHelp
    {
        public static void LoadLuaFile(string filePath)
        {
            App.instance.lua.DoString(string.Format("require \'{0}\'", filePath));
        }
    }
}