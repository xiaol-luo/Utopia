
using System;
using System.IO;
using System.Text.RegularExpressions;
using UnityEngine;
using Utopia;

namespace Utopia
{
    public class AppStateAwakeLua : AppStateBase
    {
        public AppStateAwakeLua(AppStateMgr stateMgr) : base(stateMgr, EAppState.AwakeLua)
        {

        }

        bool isInited = false;
        public override void Enter(object param)
        {
            if (!isInited)
            {
                isInited = true;

                App.instance.lua.AddBuildin("rapidjson", XLua.LuaDLL.Lua.LoadRapidJson);

                App.instance.lua.AddLoader(LuaFileLoader);

                App.instance.lua.DoString("CS.UnityEngine.Debug.Log('AppStateAwakeLua Enter')");

                App.instance.lua.DoString("require  'global_def.lua'");
                App.instance.lua.DoString("require  'setting_loadfiles.lua'");
                App.instance.lua.DoString("require  'do_loadfiles.lua'");

                Lua.LuaHelp.ReloadScripts("_load_files_libs");
            }
        }

        byte[] LuaFileLoader(ref string filePath)
        {
            Match m = Regex.Match(filePath, @".+\.lua");
            if (!m.Success)
            {
                return null;
            }

            string luaRootDir = Path.Combine(Application.dataPath, "Res/Lua");
            string luaFile = Path.Combine(luaRootDir, filePath);
            if (!File.Exists(luaFile))
                return null;

            filePath = luaFile;
            byte[] bins = File.ReadAllBytes(luaFile);
            return bins;
        }

        public override void Exit()
        {
            App.instance.lua.DoString("CS.UnityEngine.Debug.Log('AppStateAwakeLua Exit')");
        }

        public override void Update()
        {
            if (isInited)
            {
                m_stateMgr.ChangeState(EAppState.WaitTask, null);
            }
        }
    }
}

