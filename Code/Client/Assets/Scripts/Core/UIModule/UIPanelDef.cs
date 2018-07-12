namespace Utopia.UI
{
    public class UIShowPanelDataBase
    {

    }

    public enum UIPanelId
    {
        None = 0,
        MainPanel,
        LoadingPanel,
        ConfirmPanel,

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
        Loading,
        Count,
    }

    public enum UIPanelShowMode
    {
        Coexist,        // 共存
        Mask,           // 遮挡下层Panel
        HideOther,      // 隐藏其他， 这里同时只存在一个全屏panel，若是新show一个全屏panel，新的顶替旧的
        UponHideOther,  // 在隐藏其他模式的面板之上
        Loading,        // 加载面板层，在最上边遮挡所有UI
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
                    case UIPanelShowMode.Loading:
                        ret = UIPanelLayer.Loading;
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
        public static bool InFullScreenLayers(UIPanelLayer panelLayer)
        {
            bool ret = false;
            switch (panelLayer)
            {
                case UIPanelLayer.FullScreen:
                case UIPanelLayer.UponFullScreen:
                    ret = true;
                    break;
            }
            return ret;
        }

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
                panelLayer = UIPanelLayer.Coexist_1,
                showMode = UIPanelShowMode.Coexist,
                resPath = "Assets/Resources/UI/Panels/MainPanel.prefab"
            };
            s_panelSettings[(int)UIPanelId.LoadingPanel] = new UIPanelSetting()
            {
                showMode = UIPanelShowMode.Loading,
                resPath = "Assets/Resources/UI/Panels/LoadingPanel.prefab"
            };
            s_panelSettings[(int)UIPanelId.ConfirmPanel] = new UIPanelSetting()
            {
                showMode = UIPanelShowMode.Mask,
                resPath = "Assets/Resources/UI/Panels/ConfirmPanel.prefab"
            };

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