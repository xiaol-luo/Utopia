
namespace Utopia.UI
{
    public interface IUIPanelBase
    {
        void Init();
        void Show(UIShowPanelDataBase panelData);
        void Reshow();
        void Hide();
        void Freeze();
        void Unfreeze();
        UIPanelSetting GetPanelSetting();
        UIPanelId GetPanelId();
        UIPanelState GetPanelState();
    }
}
