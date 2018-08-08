
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
        public override void Exit()
        {

        }

        public override void Update()
        {
            if (isInited)
            {
                m_stateMgr.ChangeState(EAppState.WaitTask, null);
            }
        }

        bool isInited = false;
        public override void Enter(object param)
        {
            if (!isInited)
            {
                isInited = true;

                {
                    // lua libs
                    App.instance.lua.AddBuildin("rapidjson", XLua.LuaDLL.Lua.LoadRapidJson);
                }
                {
                    // lua files
                    App.instance.lua.AddLoader(LuaFileLoader);
                    App.instance.lua.DoString("require  'do_loadfiles.lua'");
                }
            }
        }

        byte[] LuaFileLoader(ref string filePath)
        {
            Match m = Regex.Match(filePath, @".+\.lua");
            if (!m.Success)
            {
                return null;
            }


            string luaFile = Lua.LuaHelp.GetLuaAbsPath(filePath);
            if (!File.Exists(luaFile))
                return null;
            filePath = luaFile;
            byte[] bins = File.ReadAllBytes(luaFile);
            return bins;
        }
    }
}

