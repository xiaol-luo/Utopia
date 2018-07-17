
using System;
using UnityEngine;
using Utopia;

namespace Utopia
{
    public class AppStateAwakeCore : AppStateBase
    {
        public AppStateAwakeCore(IStateMgr stateMgr) : base(stateMgr, (int)EAppState.AwakeCore)
        {

        }

        bool isInited = false;
        public override void Enter(object param)
        {
            if (!isInited)
            {
                isInited = true;
                if (!App.instance.gameConfig.Start())
                {
                    Debug.LogError(string.Format("GameConfig Start errno :{0}, error msg :{1}", 
                        App.instance.gameConfig.errno, App.instance.gameConfig.errMsg));
                    App.instance.Quit();
                    return;
                }
                {
                    Core.instance.Awake();
                    if (CoreModule.EStage.Updating != Core.instance.currStage)
                    {
                        Debug.LogError(string.Format("Core awake fail!"));
                        App.instance.Quit();
                        return;
                    }
                }
            }
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
    }
}

