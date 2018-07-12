
using System.Collections.Generic;
using UnityEngine;

namespace Utopia.UI
{
    public partial class UIPanelMgr
    {
        public const string Default_UIPanelProxy_Res_Path = "Assets/Resources/UI/UIPanelProxy.prefab";

        static List<string> s_UIPanelProxy_Res_Paths = new List<string>() {
            Default_UIPanelProxy_Res_Path,
        };

        Transform[] m_layers = new Transform[(int)UIPanelLayer.Count];
        string[] m_layerPaths = new string[(int)UIPanelLayer.Count]
        {
            "UILayer/CoexistLayer0",
            "UILayer/CoexistLayer1",
            "UILayer/CoexistLayer2",
            "UILayer/MaskLayer",
            "UILayer/FullScreenLayer",
            "UILayer/UponFullScreenLayer",
            "UILayer/LoadingLayer",
        };

        public UIPanelMgr(GameObject panelRoot)
        {
            for (UIPanelLayer pl = UIPanelLayer.Coexist_0; pl < UIPanelLayer.Count; ++ pl)
            {
                string layerPath = m_layerPaths[(int)pl];
                m_layers[(int)pl] = panelRoot.transform.Find(layerPath);
                Core.instance.logModule.LogAssert(null != m_layers[(int)pl], "New UIPanelMgr {0} is null, can not find child {1}", pl, layerPath);
            }
        }

        IUIPanelMgrStragy m_showStragy;

        ResourceLoaderProxy m_resLoader = ResourceLoaderProxy.Create();
        Dictionary<string, ResourceObserver> m_panelProxyResMap = new Dictionary<string, ResourceObserver>();

        public ResourceObserver GetProxyGoRes(string resName)
        {
            ResourceObserver ret;
            m_panelProxyResMap.TryGetValue(resName, out ret);
            return ret;
        }

        public bool IsAllProxyResLoaded()
        {
            bool ret = true;
            foreach (var res in m_panelProxyResMap.Values)
            {
                if (!res.isLoaded)
                {
                    ret = false;
                    break;
                }
            }
            return ret;
        }

        public bool Init()
        {
            m_showStragy = new UIPanelMgrStragy(this);

            foreach (string resPath in s_UIPanelProxy_Res_Paths)
            {
               ResourceObserver resOb = m_resLoader.AsyncLoadAsset(resPath, this.OnLoadProxyResCallback);
                m_panelProxyResMap.Add(resPath, resOb);
            }
            
            return true;
        }
        void OnLoadProxyResCallback(string resPath, ResourceObserver rob)
        {
            ResourceObserver resOb = this.GetProxyGoRes(resPath);
            if (null != resOb)
            {
                if (!resOb.isLoaded)
                {
                    m_panelProxyResMap.Clear();
                    Core.instance.timerModule.Add(() => {
                        Core.instance.eventModule.Fire(Event.AppEvent.UIPanelMgr_LoadPanelProxyResourceFail);
                    }, 0); 
                }
                else
                {
                    bool isAllLoaded = true;
                    foreach (var item in m_panelProxyResMap.Values)
                    {
                        if (!item.isLoaded)
                        {
                            isAllLoaded = false;
                            break;
                        }
                    }
                    if (isAllLoaded)
                    {
                        Core.instance.eventModule.Fire(Event.AppEvent.UIPanelMgr_BecomeReady);
                    }
                }
            }
        }

        public void Destory()
        {
            m_resLoader.Release();
        }

        Dictionary<UIPanelId, UIPanelProxy> m_cachedPanels = new Dictionary<UIPanelId, UIPanelProxy>();
        public UIPanelProxy GetCachedPanel(UIPanelId panelId)
        {
            UIPanelProxy ret;
            m_cachedPanels.TryGetValue(panelId, out ret);
            return ret;
        }

        public UIPanelProxy ShowPanel(UIPanelId panelId, UIShowPanelDataBase param)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null == panelProxy)
            {
                UIPanelSetting panelSetting = UIPanelDef.GetPanelSetting(panelId);
                panelProxy = panelSetting.CreateProxy(this, panelId);
                panelProxy.Init();
                {
                    panelProxy.SetPanelOperaAction(UIPanelOpera.Showed, this.OperaShow);
                    panelProxy.SetPanelOperaAction(UIPanelOpera.Reshowed, this.OperaReshow);
                    panelProxy.SetPanelOperaAction(UIPanelOpera.Hided, this.OperaHide);
                    panelProxy.SetPanelOperaAction(UIPanelOpera.Released, this.OperaRelease);
                    panelProxy.SetPanelOperaAction(UIPanelOpera.Freezed, this.OperaFreeze);
                    panelProxy.SetPanelOperaAction(UIPanelOpera.Unfreezed, this.OperaUnfreeze);
                }
                GameObject panelRoot = panelProxy.GetRoot();
                panelRoot.transform.SetParent(m_layers[(int)panelSetting.panelLayer]);
                panelRoot.SetActive(true);
                panelRoot.transform.localPosition = Vector3.zero;
                panelRoot.transform.localScale = Vector3.one;
                m_cachedPanels.Add(panelId, panelProxy);
            }
            panelProxy.Show(param);
            return panelProxy;
        }
        public UIPanelProxy ReshowPanel(UIPanelId panelId)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null != panelProxy)
            {
                panelProxy.Reshow();
            }
            return panelProxy;
        }
        public UIPanelProxy HidePanel(UIPanelId panelId)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null != panelProxy)
            {
                panelProxy.Hide();
            }
            return panelProxy;
        }

        public void ReleasePanel(UIPanelId panelId)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null != panelProxy)
            {
                panelProxy.Release();
            }
        }

        public UIPanelId GetTopestActivePanelId()
        {
            UIPanelId ret = m_showStragy.GetTopestActivePanelId();
            return ret;
        }
    }
}
