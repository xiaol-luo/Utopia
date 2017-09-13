using UnityEngine;

public class AppStateSelectHero : IAppState
{
    public AppStateSelectHero(IStateMgr stateMgr) : base(stateMgr, (int)IAppState.StateName.SelectHero)
    {

    }

    UISelectHero m_mono = null;
    public override void Enter(params object[] objs)
    {
        m_mono = App.my.uiRoot.GetComponentInChildren<UISelectHero>();
        if (null == m_mono)
        {
            Object prefab = Resources.Load("Art/UI/Prefabs/UISelectHero");
            GameObject go = GameObject.Instantiate(prefab) as GameObject;
            m_mono = go.GetComponent<UISelectHero>();
            m_mono.transform.parent = App.my.uiRoot;
            m_mono.transform.localPosition = Vector3.zero;
            m_mono.transform.localScale = Vector3.one;
        }
    }

    public override void Exit(params object[] objs)
    {
        if (null != m_mono)
        {
            GameObject.Destroy(m_mono.gameObject);
        }
        m_mono = null;
    }

    public override void Update(params object[] objs)
    {

    }
}