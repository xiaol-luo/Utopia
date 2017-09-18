
using NetProto;

public class Scene
{
    public void EnterScene(string sceneName)
    {
        App.my.gameNetwork.Send(ProtoId.PidLoadSceneComplete);
        App.my.gameNetwork.Send(ProtoId.PidPullAllSceneInfo);
    }
    public void LeaveScene()
    {
        App.my.gameNetwork.Send(ProtoId.PidLeaveScene);
    }
}
