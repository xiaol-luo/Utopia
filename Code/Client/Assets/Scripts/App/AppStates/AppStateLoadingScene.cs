using UnityEngine;
using UnityEngine.SceneManagement;
using Utopia;

public class AppStateLoadingScene : AppStateBase
{
    public enum LoadResult
    {
        Success = 0,
        Fail,
        Break,
    }

    public AppStateLoadingScene(IStateMgr stateMgr) : base(stateMgr, (int)AppStateBase.StateName.LoadingScene)
    {

    }

    System.Action<LoadResult, string> m_cb = null;
    AsyncOperation m_asyncOpera;
    string m_sceneName = string.Empty;
    UILoadingScene m_mono = null;

    void Reset()
    {
        m_cb = null;
        m_asyncOpera = null;
        m_sceneName = string.Empty;
    }

    public override void Enter(params object[] objs)
    {
        if (null != m_asyncOpera)
        {
            if (null != m_cb)
                m_cb(LoadResult.Break, m_sceneName);
        }

        this.Reset();
        m_sceneName = objs[0] as string;
        m_cb = objs[1] as System.Action<LoadResult, string>;
        m_asyncOpera = SceneManager.LoadSceneAsync(m_sceneName);


        m_mono = App.instance.uiRoot.GetComponentInChildren<UILoadingScene>();
        if (null == m_mono)
        {
            Object prefab = Resources.Load("Art/UI/Prefabs/UILoadingScene");
            GameObject go = GameObject.Instantiate(prefab) as GameObject;
            go.SetActive(true);
            m_mono = go.GetComponent<UILoadingScene>();
            m_mono.transform.SetParent(App.instance.uiRoot);
            m_mono.transform.localPosition = Vector3.zero;
            m_mono.transform.localScale = Vector3.one;
        }

        m_mono.loadingTxt.text = "Loading";
    }

    public override void Exit(params object[] objs)
    {
        if (null != m_mono)
            GameObject.Destroy(m_mono.gameObject);
        m_mono = null;
    }

    public override void Update(params object[] objs)
    {
        if (null == m_asyncOpera)
        {
            if (null != m_cb)
            {
                m_cb(LoadResult.Fail, m_sceneName);
                this.Reset();
            }
        }
        if (null != m_asyncOpera)
        {
            if (null != m_mono)
            {
                m_mono.loadingTxt.text = string.Format("Loading {0}", m_asyncOpera.progress);
            }
            if (m_asyncOpera.isDone)
            {
                if (null != m_cb)
                    m_cb(LoadResult.Success, m_sceneName);
                this.Reset();
            }
        }
    }
}