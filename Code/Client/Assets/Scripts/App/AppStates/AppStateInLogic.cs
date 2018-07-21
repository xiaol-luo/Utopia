
using System;
using Utopia;

namespace Utopia
{
    public class AppStateInLogic : AppStateBase
    {
        public AppStateInLogic(AppStateMgr stateMgr) : base(stateMgr, EAppState.InLogic)
        {

        }

        bool isInited = false;

        public override void Enter(object param)
        {
            if (!isInited)
            {
                isInited = true;

                App.instance.net.Init();

                {
                    App.instance.logicMgr.Awake();
                }
                if (!App.instance.panelMgr.Awake())
                {
                    Core.instance.log.LogError(string.Format("panelMgr.Awake"));
                    App.instance.Quit();
                }
            }
        }

        public override void Exit()
        {

        }

        public override void Update()
        {
        }
    }
}

