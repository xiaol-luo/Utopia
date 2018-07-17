using UnityEngine;
using System.Collections;

namespace Utopia
{
    public class GameInit : MonoBehaviour
    {
        EventProxy<string> m_evProxy;

        // Use this for initialization
        void Start()
        {
            m_evProxy = Core.instance.eventMgr.CreateEventProxy();
            m_evProxy.Subscribe(Event.AppEvent.UIPanelMgr_BecomeReady, (string eventName)=> {
                App.instance.panelMgr.ShowPanel(UI.UIPanelId.MainPanel);
            });

            AppStateWaitTask appState = App.instance.stateMgr.GetState(EAppState.WaitTask) as AppStateWaitTask;
            appState.SetTask(()=> {
                App.instance.stateMgr.ChangeState(EAppState.InLogic, null);
            });
        }

        // Update is called once per frame
        void Update()
        {
        }

        void OnDestroy()
        {
            
        }
    }
}

