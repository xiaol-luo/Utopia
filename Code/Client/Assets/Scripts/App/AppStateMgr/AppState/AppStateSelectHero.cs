using NetProto;
using UnityEngine;

public class AppStateSelectHero : IAppState
{
    public AppStateSelectHero(IStateMgr stateMgr) : base(stateMgr, (int)IAppState.StateName.SelectHero)
    {

    }

    ulong m_red_hero_id = 0;
    ulong m_blue_hero_id = 0;
    string m_err_msg = string.Empty;
    UISelectHero m_mono = null;
    public override void Enter(params object[] objs)
    {
        m_mono = App.my.uiRoot.GetComponentInChildren<UISelectHero>();
        if (null == m_mono)
        {
            Object prefab = Resources.Load("Art/UI/Prefabs/UISelectHero");
            GameObject go = GameObject.Instantiate(prefab) as GameObject;
            m_mono = go.GetComponent<UISelectHero>();
            m_mono.transform.SetParent(App.my.uiRoot);
            m_mono.transform.localPosition = Vector3.zero;
            m_mono.transform.localScale = Vector3.one;
        }

        m_mono.gameObject.SetActive(true);
        m_mono.redHeroBtn.onClick.RemoveAllListeners();
        m_mono.redHeroBtn.onClick.AddListener(() => { this.OnClickBtn(true); });
        m_mono.blueHeroBtn.onClick.RemoveAllListeners();
        m_mono.blueHeroBtn.onClick.AddListener(() => { this.OnClickBtn(false); });
        string m_err_msg = string.Empty;
        m_red_hero_id = 0;
        m_blue_hero_id = 0;
        this.UpdateUI();

        App.my.gameNetwork.Add<RspFreeHero>((int)ProtoId.PidRspFreeHero, this.RspFreeHero);
        App.my.gameNetwork.Add<SelectHeroRsp>((int)ProtoId.PidSelectHeroRsp, this.SelectHeroRsp);
        App.my.gameNetwork.Send((int)ProtoId.PidQueryFreeHero);

    }

    public override void Exit(params object[] objs)
    {
        if (null != m_mono)
        {
            GameObject.Destroy(m_mono.gameObject);
        }
        m_mono = null;
        App.my.gameNetwork.Remove((int)ProtoId.PidRspFreeHero);
        App.my.gameNetwork.Remove((int)ProtoId.PidSelectHeroRsp);
    }

    public override void Update(params object[] objs)
    {

    }
    void RspFreeHero(int id, RspFreeHero msg)
    {
        m_red_hero_id = msg.RedHeroId;
        m_blue_hero_id = msg.BlueHeroId;
        this.UpdateUI();
    }

    void SelectHeroRsp(int id, SelectHeroRsp msg)
    {
        if (msg.IsSucc)
            m_err_msg = "select ok";
        else
            m_err_msg = "select hero fail";
        this.UpdateUI();

        if (msg.IsSucc)
        {
            App.my.heroId = msg.HeroId;
            System.Action<AppStateLoadingScene.LoadResult, string> cb = this.EnterStateInBattle;
            m_stateMgr.ChangeState(IAppState.StateName.LoadingScene, "Level_Battle", cb);
        }
    }

    void EnterStateInBattle(AppStateLoadingScene.LoadResult ret, string sceneName)
    {
        if (AppStateLoadingScene.LoadResult.Success == ret)
            m_stateMgr.ChangeState(IAppState.StateName.InBattle, sceneName);
    }

    void UpdateUI()
    {
        if (null != m_mono)
        {
            m_mono.errMsgTxt.text = m_err_msg;
            m_mono.redHeroBtn.gameObject.SetActive(m_red_hero_id > 0);
            m_mono.blueHeroBtn.gameObject.SetActive(m_blue_hero_id > 0);
        }
    }

    void OnClickBtn(bool isRedBtn)
    {
        ulong hero_id = 0;
        if (isRedBtn)
            hero_id = m_red_hero_id;
        if (!isRedBtn)
            hero_id = m_blue_hero_id;
        if (hero_id > 0)
        {
            SelectHeroReq req = new SelectHeroReq() { HeroId = hero_id };
            App.my.gameNetwork.Send((int)ProtoId.PidSelectHeroReq, req);
        }
    }
}