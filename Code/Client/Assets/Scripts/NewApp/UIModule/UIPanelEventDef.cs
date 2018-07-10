namespace Utopia.UI
{
    public static class UIPanelEventDef
    {
        public class PanelIdChange
        {
            public UIPanelId from = UIPanelId.None;
            public UIPanelId to = UIPanelId.None;
        }

        public const string FullScreenPanelOnTop = "FullScreenPanelOnTop";
        public const string FullScreenPanelNotOnTop = "FullScreenPanelNotOnTop";
    }
}
