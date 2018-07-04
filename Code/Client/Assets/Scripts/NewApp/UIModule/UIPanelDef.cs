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
        Bg,
        Normal,
        Tool,
        Alter,
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
        public UIPanelLayer panelLayer = UIPanelLayer.Normal;
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
                panelLayer = UIPanelLayer.Normal,
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