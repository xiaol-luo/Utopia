
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

            UnityEngine.Application.targetFrameRate = SceneDef.InBattle_GameFrame;
            
        }

        public override void Exit()
        {
            App.instance.scene.LeaveScene();
            UnityEngine.Application.targetFrameRate = SceneDef.InLogic_GameFrame;
        }

        public override void Update()
        {
            App.instance.scene.FixUpdate();
        }
    }
}
