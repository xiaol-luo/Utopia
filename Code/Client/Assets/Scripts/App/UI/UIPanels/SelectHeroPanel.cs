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

        [SerializeField]
        Button refresh;

        protected override void OnInit()
        {
            base.OnInit();

            m_evProxy.Subscribe(SelectHeroModuleDef.Event_OnRspFreeHeros, OnRspFreeHero);
            m_evProxy.Subscribe(SelectHeroModuleDef.Event_OnRspSelectHero, OnRspFSelectHero);

            hero1Btn.onClick.AddListener(()=> {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.SelectSide(Logic.SelectHero.SelectedSide.RedSide);
            });
            hero2Btn.onClick.AddListener(() => {
                Logic.SelectHero module = App.instance.logicMgr.GetModule<Logic.SelectHero>();
                module.SelectSide(Logic.SelectHero.SelectedSide.BlueSide);
            });
            refresh.onClick.AddListener(() => {
                App.instance.logicMgr.GetModule<Logic.SelectHero>().QueryFreeHero();
            });
        }

        void OnRspFreeHero(string evName)
        {
            this.UpdateUI();
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
