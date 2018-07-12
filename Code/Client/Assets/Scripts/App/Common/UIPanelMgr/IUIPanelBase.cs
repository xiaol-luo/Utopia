
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
        Freezed,
        Unfreezed,
        PreRelease,
        Released,
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
        void Release();
        UIPanelSetting GetPanelSetting();
        UIPanelId GetPanelId();
        UIPanelState GetPanelState();
        bool IsFreezed();
        bool IsLoading();
        bool IsReleased();
        bool IsReady();
    }
}
