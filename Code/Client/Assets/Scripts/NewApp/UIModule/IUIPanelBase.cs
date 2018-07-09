
namespace Utopia.UI
{
    public enum UIPanelOpera
    {
        PreShow,
        Showed,
        PreReshowed,
        Reshowed,
        PreHide,
        Hided,
        Count,
    }

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
        bool IsLoading();
        bool IsReleased();
        bool IsReady();
    }
}
