namespace Utopia.UI
{
    public class UIShowPanelDataBase
    {
        public object openCbParam;
        public System.Action<IUIPanelBase, object> openCb;
    }

    public enum UIPanelId
    {
        None = 0,
        MainPanel,
        MainPanel_1,
        MainPanel_2,
        MainPanel_3,
        MainPanel_4,
        MainPanel_5,

        MainPanel_00,
        MainPanel_11,
        MainPanel_22,
        MainPanel_33,
        MainPanel_44,
        MainPanel_55,

        MainPanel_000,
        MainPanel_111,
        MainPanel_222,
        MainPanel_333,
        MainPanel_444,
        MainPanel_555,

        ReserveName_Begin,
        ReserveName_End = ReserveName_Begin + 20,
        Count,
    }

    public enum UIPanelLayer
    {
        Coexist_0,
        Coexist_1,
        Coexist_2,
        Mask,
        FullScreen,
        UponFullScreen,
        Count,
    }

    public enum UIPanelShowMode
    {
        Coexist,        // 共存
        Mask,           // 遮挡下层Panel
        HideOther,      // 隐藏其他， 这里同时只存在一个全屏panel，若是新show一个全屏panel，新的顶替旧的
        UponHideOther,  // 在隐藏其他模式的面板之上
        Count,
    }

    public enum UIPanelState
    {
        Free = 0,
        Loading,
        Loaded,
        Hided,
        Showed,
        Released,
    }

    public class UIPanelSetting
    {
        protected UIPanelLayer m_panelLayer;
        public UIPanelLayer panelLayer
        {
            get
            {
                UIPanelLayer ret = UIPanelLayer.Coexist_0;
                switch (showMode)
                {
                    case UIPanelShowMode.Mask:
                        ret = UIPanelLayer.Mask;
                        break;
                    case UIPanelShowMode.HideOther:
                        ret = UIPanelLayer.FullScreen;
                        break;
                    case UIPanelShowMode.UponHideOther:
                        ret = UIPanelLayer.UponFullScreen;
                        break;
                    default:
                        {
                            switch (m_panelLayer)
                            {
                                case UIPanelLayer.Coexist_0:
                                case UIPanelLayer.Coexist_1:
                                case UIPanelLayer.Coexist_2:
                                    ret = m_panelLayer;
                                    break;
                            }
                        }
                        break;
                }
                return ret;
            }
            set
            {
                m_panelLayer = value;
            }
        }
        public UIPanelShowMode showMode;
        public string resPath = string.Empty;

        public virtual UIPanelProxy CreateProxy(UIPanelMgr panelMgr, UIPanelId panelId)
        {
            return new UIPanelProxy(panelMgr, panelId);
        }
    }

    public static class UIPanelDef
    {
        static UIPanelSetting[] s_panelSettings = new UIPanelSetting[(int)UIPanelId.Count];

        public static void SetPanelSetting(UIPanelId panelId, UIPanelSetting setting)
        {
            SetPanelSetting((int)panelId, setting);
        }
        public static void SetPanelSetting(int panelId, UIPanelSetting setting)
        {
            s_panelSettings[panelId] = setting;
        }
        public static UIPanelSetting GetPanelSetting(UIPanelId panelId)
        {
            return GetPanelSetting((int)panelId);
        }
        public static UIPanelSetting GetPanelSetting(int panelId)
        {
            UIPanelSetting ret = s_panelSettings[panelId];
            return ret;
        }

        // 请在这里调用函数初始化所有panel的settting
        public static void InitPanelSettings()
        {
            s_panelSettings[(int)UIPanelId.MainPanel] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.Coexist_0,
                showMode = UIPanelShowMode.Coexist,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
            };

            s_panelSettings[(int)UIPanelId.MainPanel_1] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.Coexist_1,
                showMode = UIPanelShowMode.Coexist,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
            };

            s_panelSettings[(int)UIPanelId.MainPanel_2] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.Coexist_2,
                showMode = UIPanelShowMode.Coexist,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
            };

            s_panelSettings[(int)UIPanelId.MainPanel_3] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.Mask,
                showMode = UIPanelShowMode.Mask,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
            };

            s_panelSettings[(int)UIPanelId.MainPanel_4] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.FullScreen,
                showMode = UIPanelShowMode.HideOther,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
            };
            s_panelSettings[(int)UIPanelId.MainPanel_5] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.UponFullScreen,
                showMode = UIPanelShowMode.UponHideOther,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
            };

            {
                s_panelSettings[(int)UIPanelId.MainPanel_00] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Coexist_0,
                    showMode = UIPanelShowMode.Coexist,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_11] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Coexist_1,
                    showMode = UIPanelShowMode.Coexist,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_22] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Coexist_2,
                    showMode = UIPanelShowMode.Coexist,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_33] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Mask,
                    showMode = UIPanelShowMode.Mask,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_44] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.FullScreen,
                    showMode = UIPanelShowMode.HideOther,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };
                s_panelSettings[(int)UIPanelId.MainPanel_55] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.UponFullScreen,
                    showMode = UIPanelShowMode.UponHideOther,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };
            }

            {
                s_panelSettings[(int)UIPanelId.MainPanel_000] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Coexist_0,
                    showMode = UIPanelShowMode.Coexist,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_111] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Coexist_1,
                    showMode = UIPanelShowMode.Coexist,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_222] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Coexist_2,
                    showMode = UIPanelShowMode.Coexist,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_333] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.Mask,
                    showMode = UIPanelShowMode.Mask,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };

                s_panelSettings[(int)UIPanelId.MainPanel_444] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.FullScreen,
                    showMode = UIPanelShowMode.HideOther,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };
                s_panelSettings[(int)UIPanelId.MainPanel_555] = new UIPanelSetting()
                {
                    panelLayer = UIPanelLayer.UponFullScreen,
                    showMode = UIPanelShowMode.UponHideOther,
                    resPath = "Assets/Resources/UI/MainPanel.prefab"
                };
            }

            {
                // reservt ids use default setting
                for (UIPanelId id = UIPanelId.ReserveName_Begin; id < UIPanelId.Count; ++ id)
                {
                    s_panelSettings[(int)id] = new UIPanelSetting();
                }
            }
        }
    }
}