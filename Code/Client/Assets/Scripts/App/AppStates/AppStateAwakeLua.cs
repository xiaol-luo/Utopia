
using System;
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

                App.instance.lua.DoString("CS.UnityEngine.Debug.Log('AppStateAwakeLua Enter')");
            }
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

