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

        protected override void OnInit()
        {
            base.OnInit();

            m_evProxy.Subscribe(SelectHeroModuleDef.Event_OnRspFreeHeros, OnRspFreeHero);
            m_evProxy.Subscribe(SelectHeroModuleDef.Event_OnRspSelectHero, OnRspFSelectHero);

            hero1Btn.onClick.AddListener(()=> {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.SelectHeroReq(module.redHeroId);
            });
            hero2Btn.onClick.AddListener(() => {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.SelectHeroReq(module.blueHeroId);
            });
        }

        void OnRspFreeHero(string evName)
        {
            this.UpdateUI();
            Logic.SelectHero logicSelectHero = App.instance.logicMgr.GetModule<Logic.SelectHero>();
            if (logicSelectHero.usingHeroObjId > 0)
            {
                if (App.instance.stateMgr.activeId != EAppState.InBattle)
                {
                    App.instance.stateMgr.ChangeState(EAppState.InBattle);
                }
            }
        }
        void OnRspFSelectHero(string evName)
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
