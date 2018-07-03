
namespace Utopia.UI
{
    interface IUIPanelBase
    {
        bool ShowPanel(System.Action<IUIPanelBase> cb);
        bool HidePanel();

    }
}
