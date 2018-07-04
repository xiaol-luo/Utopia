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
        Coexist,        // ����
        Mask,           // �ڵ��²�Panel
        HideOther,      // ���������� ����ͬʱֻ����һ��ȫ��panel��������showһ��ȫ��panel���µĶ���ɵ�
        UponHideOther,  // ����������ģʽ�����֮��
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

        // ����������ú�����ʼ������panel��settting
        public static void InitPanelSettings()
        {
            s_panelSettings[(int)UIPanelId.MainPanel] = new UIPanelSetting()
            {
                panelLayer = UIPanelLayer.Coexist_0,
                showMode = UIPanelShowMode.Coexist,
                resPath = "Assets/Resources/UI/MainPanel.prefab"
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