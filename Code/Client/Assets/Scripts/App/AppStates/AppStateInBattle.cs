
using System;
using Utopia;

namespace Utopia
{
    public class AppStateInBattle : AppStateBase
    {
        public AppStateInBattle(IStateMgr stateMgr) : base(stateMgr, (int)EAppState.InBattle)
        {

        }

        public override void Enter(object param)
        {
            string sceneName = param as string;
            App.instance.scene.EnterScene(sceneName);
        }

        public override void Exit()
        {

        }

        public override void Update()
        {
            App.instance.scene.Update();
        }
    }
}
