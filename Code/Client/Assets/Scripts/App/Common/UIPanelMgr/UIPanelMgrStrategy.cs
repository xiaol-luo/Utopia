using System.Collections.Generic;

namespace Utopia.UI
{
    public partial class UIPanelMgr
    {
        public interface IUIPanelMgrStragy
        {
            void OnShowPanel(UIPanelProxy panel);
            void OnHidePanel(UIPanelProxy panel);
            void OnReshowPanel(UIPanelProxy panel);
            void OnReleasePanel(UIPanelProxy panel);
            UIPanelId GetTopestActivePanelId();
        }

        public class UIPanelInfoSet
        {
            static Dictionary<UIPanelShowMode, List<UIPanelLayer>> s_modeLayersMap = new Dictionary<UIPanelShowMode, List<UIPanelLayer>>
            {
                {UIPanelShowMode.Coexist, new List<UIPanelLayer>() { UIPanelLayer.Coexist_2, UIPanelLayer.Coexist_1, UIPanelLayer.Coexist_0, } },
                {UIPanelShowMode.Mask, new List<UIPanelLayer>() { UIPanelLayer.Mask } },
                {UIPanelShowMode.HideOther, new List<UIPanelLayer>() { UIPanelLayer.FullScreen } },
                {UIPanelShowMode.UponHideOther, new List<UIPanelLayer>() { UIPanelLayer.UponFullScreen } },
                {UIPanelShowMode.Loading, new List<UIPanelLayer>() { UIPanelLayer.Loading } },
            };

            public class PanelInfo
            {
                public UIPanelId panelId;
                public UIPanelSetting setting;
                public bool isActive = false;
                public bool isRelease = false;
                public bool isFreeze = false;
            }
            public Dictionary<UIPanelId, PanelInfo> panelInfos = new Dictionary<UIPanelId, PanelInfo>();
            public List<PanelInfo>[] layerPanelInfos = new List<PanelInfo>[(int)UIPanelLayer.Count];

            public UIPanelInfoSet()
            {
                for (int i = 0; i < layerPanelInfos.Length; ++ i)
                {
                    layerPanelInfos[i] = new List<PanelInfo>();
                }
            }

            public PanelInfo GetPanelInfo(UIPanelId panelId)
            {
                PanelInfo ret;
                panelInfos.TryGetValue(panelId, out ret);
                return ret;
            }

            public UIPanelLayer ShowPanel(UIPanelId panelId)
            {
                PanelInfo pi = this.GetPanelInfo(panelId);
                if (null == pi)
                {
                    pi = new PanelInfo();
                    pi.panelId = panelId;
                    pi.isActive = false;
                    pi.setting = UIPanelDef.GetPanelSetting(panelId);
                    panelInfos.Add(pi.panelId, pi);
                }
                else
                {
                    this.ReleasePanel(pi.panelId);
                }
                pi.isActive = true;
                layerPanelInfos[(int)pi.setting.panelLayer].Add(pi);
                return pi.setting.panelLayer;
            }
            public UIPanelLayer HidePanel(UIPanelId panelId)
            {
                UIPanelLayer ret = UIPanelLayer.Count;
                PanelInfo pi = this.GetPanelInfo(panelId);
                if (null != pi)
                {
                    ret = pi.setting.panelLayer;
                    pi.isActive = false;
                }
                return ret;
            }
            public UIPanelLayer ReshowPanel(UIPanelId panelId)
            {
                UIPanelLayer ret = UIPanelLayer.Count;
                PanelInfo pi = this.GetPanelInfo(panelId);
                if (null != pi)
                {
                    ret = pi.setting.panelLayer;
                    pi.isActive = true;
                }
                return ret;
            }

            public UIPanelLayer FreezePanel(UIPanelId panelId)
            {
                UIPanelLayer ret = UIPanelLayer.Count;
                PanelInfo pi = this.GetPanelInfo(panelId);
                if (null != pi)
                {
                    ret = pi.setting.panelLayer;
                    pi.isFreeze = true;
                }
                return ret;
            }

            public UIPanelLayer UnfreezePanel(UIPanelId panelId)
            {

                UIPanelLayer ret = UIPanelLayer.Count;
                PanelInfo pi = this.GetPanelInfo(panelId);
                if (null != pi)
                {
                    ret = pi.setting.panelLayer;
                    pi.isFreeze = false;
                }
                return ret;
            }

            public UIPanelLayer ReleasePanel(UIPanelId panelId)
            {
                UIPanelLayer ret = UIPanelLayer.Count;
                PanelInfo pi = this.GetPanelInfo(panelId);
                if (null != pi)
                {
                    ret = pi.setting.panelLayer;
                    layerPanelInfos[(int)ret].Remove(pi);
                    pi.isRelease = true;
                }
                return ret;
            }

            public PanelInfo GetTopShowedPanelInfo(UIPanelShowMode showModel)
            {
                PanelInfo ret = null;
                List<UIPanelLayer> searchLayers = null;
                if (s_modeLayersMap.TryGetValue(showModel, out searchLayers))
                {
                    foreach (UIPanelLayer layerIdx in searchLayers)
                    {
                        if (null != ret)
                            break;

                        List<PanelInfo> PanelInfoList = layerPanelInfos[(int)layerIdx];
                        foreach (PanelInfo pi in PanelInfoList)
                        {
                            if (pi.isActive)
                            {
                                ret = pi;
                                break;
                            }
                        }
                    }
                }
                return ret;
            }
            public PanelInfo GetTopestShowedPanelInfo()
            {
                PanelInfo ret = null;
                for (UIPanelShowMode i = UIPanelShowMode.Count - 1; i >= 0; --i)
                {
                    ret = this.GetTopShowedPanelInfo(i);
                    if (null != ret)
                        break;
                }
                return ret;
            }
        }
        public class UIPanelMgrStragy : IUIPanelMgrStragy
        {
            UIPanelInfoSet m_panelInfoSet = new UIPanelInfoSet();

            protected UIPanelMgr m_panelMgr;
            public UIPanelMgrStragy(UIPanelMgr panelMgr)
            {
                m_panelMgr = panelMgr;
            }

            public void OnHidePanel(UIPanelProxy panel)
            {
                UIPanelId hidedPanelId = panel.GetPanelId();

                UIPanelInfoSet.PanelInfo oldTopestPanel = m_panelInfoSet.GetTopestShowedPanelInfo();
                m_panelInfoSet.HidePanel(hidedPanelId);
                UIPanelInfoSet.PanelInfo newTopestPanel = m_panelInfoSet.GetTopestShowedPanelInfo();

                if (null != oldTopestPanel && null != newTopestPanel)
                {
                    if (hidedPanelId == oldTopestPanel.panelId)
                    {
                        if (oldTopestPanel.setting.showMode > UIPanelShowMode.Coexist)
                        {
                            if (null != newTopestPanel)
                            {
                                if (newTopestPanel.setting.showMode > UIPanelShowMode.Coexist)
                                {
                                    if (newTopestPanel.isFreeze)
                                    {
                                        var newTopestPanelProxy = m_panelMgr.GetCachedPanel(newTopestPanel.panelId);
                                        if (null != newTopestPanelProxy)
                                        {
                                            newTopestPanelProxy.Unfreeze();
                                        }
                                    }
                                }
                                else
                                {
                                    foreach (UIPanelInfoSet.PanelInfo pi in m_panelInfoSet.panelInfos.Values)
                                    {
                                        if (pi.isActive && !pi.isRelease && pi.isFreeze && UIPanelShowMode.Coexist == pi.setting.showMode)
                                        {
                                            var pp = m_panelMgr.GetCachedPanel(pi.panelId);
                                            if (null != pp)
                                            {
                                                pp.Unfreeze();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                this.CheckFullScreenOnTop(oldTopestPanel, newTopestPanel);
            }

            void CheckFullScreenOnTop(UIPanelInfoSet.PanelInfo oldTopestPanel, UIPanelInfoSet.PanelInfo newTopestPanel)
            {
                UIPanelLayer newTopestLayer = UIPanelLayer.Coexist_0;
                UIPanelEventDef.PanelIdChange pic = new UIPanelEventDef.PanelIdChange();
                if (null != oldTopestPanel)
                {
                    pic.from = oldTopestPanel.panelId;
                }
                if (null != newTopestPanel)
                {
                    pic.to = newTopestPanel.panelId;
                    newTopestLayer = newTopestPanel.setting.panelLayer;
                }
                if (pic.from != pic.to)
                {
                    if (UIPanelDef.InFullScreenLayers(newTopestLayer))
                    {
                        Core.instance.eventMgr.Fire(UIPanelEventDef.FullScreenPanelOnTop, pic);
                    }
                    else
                    {
                        Core.instance.eventMgr.Fire(UIPanelEventDef.FullScreenPanelNotOnTop, pic);
                    }
                }
            }

            public void OnReleasePanel(UIPanelProxy panel)
            {
                m_panelInfoSet.ReleasePanel(panel.GetPanelId());
            }

            public void OnReshowPanel(UIPanelProxy panel)
            {
                UIPanelInfoSet.PanelInfo oldTopestPanel = m_panelInfoSet.GetTopestShowedPanelInfo();
                m_panelInfoSet.ReshowPanel(panel.GetPanelId());
                UIPanelInfoSet.PanelInfo newTopestPanel = m_panelInfoSet.GetTopestShowedPanelInfo();
                this.CheckShowFreeze(panel, oldTopestPanel, newTopestPanel);
            }

            public void OnShowPanel(UIPanelProxy panel)
            {
                panel.GetRoot().transform.SetAsLastSibling();
                UIPanelId showedPanelId = panel.GetPanelId();
                UIPanelInfoSet.PanelInfo oldTopestPanel = m_panelInfoSet.GetTopestShowedPanelInfo();
                m_panelInfoSet.ShowPanel(showedPanelId);
                UIPanelInfoSet.PanelInfo newTopestPanel = m_panelInfoSet.GetTopestShowedPanelInfo();
                this.CheckShowFreeze(panel, oldTopestPanel, newTopestPanel);
            }

            void CheckShowFreeze(UIPanelProxy showedPanelProxy, UIPanelInfoSet.PanelInfo oldTopestPanel, UIPanelInfoSet.PanelInfo newTopestPanel)
            {
                UIPanelId showedPanelId = showedPanelProxy.GetPanelId();
                if (null != oldTopestPanel)
                {
                    if (newTopestPanel.panelId != showedPanelId)
                    {
                        // 新showed的面板并不在最上层，那么新show的面板也不会导致其他面板freeze
                        // 判断下是否冻结自己就好了
                        if (!newTopestPanel.isFreeze && newTopestPanel.setting.showMode > UIPanelShowMode.Coexist)
                        {
                            showedPanelProxy.Freeze();
                        }
                    }
                    else
                    {
                        // 新show的面板如果在最上层, 并且之前新show的面板并不在最上层，那么可能要把其面板冻结掉
                        if (oldTopestPanel != newTopestPanel)
                        {
                            if (newTopestPanel.setting.showMode > UIPanelShowMode.Coexist)
                            {
                                if (oldTopestPanel.setting.showMode != UIPanelShowMode.Coexist)
                                {
                                    if (!oldTopestPanel.isFreeze)
                                    {
                                        var oldTopestPanelProxy = m_panelMgr.GetCachedPanel(oldTopestPanel.panelId);
                                        if (null != oldTopestPanelProxy)
                                        {
                                            oldTopestPanelProxy.Freeze();
                                        }
                                    }
                                }
                                else // 如果旧的最高层面板是共存类型的，那么可能所有共存类型的面板都需要Freeze下
                                {
                                    foreach (UIPanelInfoSet.PanelInfo pi in m_panelInfoSet.panelInfos.Values)
                                    {
                                        if (pi.isActive && !pi.isRelease && !pi.isFreeze && UIPanelShowMode.Coexist == pi.setting.showMode)
                                        {
                                            var pp = m_panelMgr.GetCachedPanel(pi.panelId);
                                            if (null != pp)
                                            {
                                                pp.Freeze();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                this.CheckFullScreenOnTop(oldTopestPanel, newTopestPanel);
            }

            public UIPanelId GetTopestActivePanelId()
            {
                UIPanelId ret = UIPanelId.None;
                UIPanelInfoSet.PanelInfo pi = m_panelInfoSet.GetTopestShowedPanelInfo();
                if (null != pi)
                {
                    ret = pi.panelId;
                }
                return ret;
            }
        }
    }
}