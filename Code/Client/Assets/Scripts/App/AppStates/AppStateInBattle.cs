
using System;
using Utopia;

namespace Utopia
{
    public class AppStateInBattle : AppStateBase
    {
        public AppStateInBattle(AppStateMgr stateMgr) : base(stateMgr, EAppState.InBattle)
        {
             
        }

        public override void Enter(object param)
        {
            App.instance.panelMgr.HideAllPanels();
            string sceneName = param as string;
            App.instance.scene.EnterScene(sceneName);
        }

        public override void Exit()
        {
            App.instance.scene.LeaveScene();
        }

        public override void Update()
        {
            App.instance.scene.Update();
        }
    }
}
