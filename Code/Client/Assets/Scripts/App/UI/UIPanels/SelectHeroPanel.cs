using NetProto;
using UnityEngine;
using UnityEngine.UI;
using Utopia.Net;

namespace Utopia.UI
{
    public class SelectHeroPanel : UIPanelBase
    {
        [SerializeField]
        Button hero1Btn;

        [SerializeField]
        Button hero2Btn;

        void OnDestroy()
        {
            m_proxy.eventProxy.ClearAll();
        }

        protected override void OnInit()
        {
            base.OnInit();

            m_proxy.eventProxy.Subscribe(SelectHeroModuleDef.Event_OnRspFreeHeros, OnEvent);
            m_proxy.eventProxy.Subscribe(SelectHeroModuleDef.Event_OnRspSelectHero, OnEvent);

            hero1Btn.onClick.AddListener(()=> {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.SelectHeroReq(module.redHeroId);
            });
            hero2Btn.onClick.AddListener(() => {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.SelectHeroReq(module.blueHeroId);
            });
        }

        void OnEvent(string evName)
        {
            this.UpdateUI();
        }

        void UpdateUI()
        {
            Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
            hero1Btn.gameObject.SetActive(module.redHeroId > 0);
            hero2Btn.gameObject.SetActive(module.blueHeroId > 0);
        }
    }
}
