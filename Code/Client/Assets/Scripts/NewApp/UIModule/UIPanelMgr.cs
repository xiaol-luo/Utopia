
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
            "UILayerFullScreen/CoexistLayer",
            "UILayerFullScreen/MaskLayer",
        };

        public UIPanelMgr(GameObject panelRoot)
        {
            for (UIPanelLayer pl = UIPanelLayer.Coexist_0; pl < UIPanelLayer.Count; ++ pl)
            {
                string layerPath = m_layerPaths[(int)pl];
                m_layers[(int)pl] = panelRoot.transform.Find(layerPath);
                NewApp.instance.logModule.LogAssert(null != m_layers[(int)pl], "New UIPanelMgr {0} is null, can not find child {1}", pl, layerPath);
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

        public bool Init()
        {
            m_showStragy = new UIPanelMgrStragy(this);

            foreach (string resPath in s_UIPanelProxy_Res_Paths)
            {
               ResourceObserver resOb = m_resLoader.AsyncLoadAsset(resPath, null);
                m_panelProxyResMap.Add(resPath, resOb);
            }
            
            return true;
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

        public void ShowPanel(UIPanelId panelId, UIShowPanelDataBase param)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null == panelProxy)
            {
                UIPanelSetting panelSetting = UIPanelDef.GetPanelSetting(panelId);
                panelProxy = panelSetting.CreateProxy(this, panelId);
                panelProxy.Init();
                m_cachedPanels.Add(panelId, panelProxy);
                panelProxy.GetRoot().transform.SetParent(m_layers[(int)panelSetting.panelLayer]);
            }
            panelProxy.Show(param);
            m_showStragy.OnShowPanel(panelProxy);
        }
        public void ReshowPanel(UIPanelId panelId)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null != panelProxy)
            {
                panelProxy.Reshow();
                m_showStragy.OnReshowPanel(panelProxy);
            }
        }
        public void HidePanel(UIPanelId panelId)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null != panelProxy)
            {
                panelProxy.Hide();
                m_showStragy.OnHidePanel(panelProxy);
            }
        }

        public void ReleasePanel(UIPanelId panelId)
        {
            UIPanelProxy panelProxy = this.GetCachedPanel(panelId);
            if (null != panelProxy)
            {
                this.HidePanel(panelId);
                m_cachedPanels.Remove(panelId);
                panelProxy.Release();
                m_showStragy.OnReleasePanel(panelProxy);
                GameObject.Destroy(panelProxy.GetRoot());
            }
        }
    }
}
