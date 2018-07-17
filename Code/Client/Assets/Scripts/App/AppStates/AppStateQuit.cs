
using System;
using Utopia;
using Utopia.Event;

namespace Utopia
{
    public class AppStateQuit : AppStateBase
    {
        public AppStateQuit(IStateMgr stateMgr) : base(stateMgr, (int)EAppState.Quit)
        {

        }

        public override void Enter(object param)
        {
            Core.instance.eventMgr.Fire(AppEvent.GameToQuit);
            App.instance.panelMgr.Destory();
            App.instance.logicMgr.Release();
            Core.instance.Release();
        }

        public override void Exit()
        {

        }

        public override void Update()
        {
        }
    }
}

