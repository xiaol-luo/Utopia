
using NetProto;

public class Scene
{
    public void EnterScene(string sceneName)
    {
        App.my.gameNetwork.Send(ProtoId.PidLoadSceneComplete);
        App.my.gameNetwork.Send(ProtoId.PidPullAllSceneInfo);

        App.my.gameNetwork.Add<AllSceneObjectState>((int)ProtoId.PidPullAllSceneInfo, OnPullAllSceneObject);
        App.my.gameNetwork.Add<SceneObjectState>((int)ProtoId.PidSceneObjectState, OnRecvSceneObjectState);
        App.my.gameNetwork.Add<MoveObjectState>((int)ProtoId.PidMoveObjectState, OnRecvMoveObjectState);
        App.my.gameNetwork.Add<MoveObjectMutableState>((int)ProtoId.PidMoveObjectMutableState, OnRecvMoveObjectMutableState);
    }
    public void LeaveScene()
    {
        App.my.gameNetwork.Send(ProtoId.PidLeaveScene);
    }


    void OnPullAllSceneObject(int id, AllSceneObjectState msg)
    {

    }

    void OnRecvSceneObjectState(int id, SceneObjectState msg)
    {

    }

    void OnRecvMoveObjectState(int id, MoveObjectState msg)
    {

    }
    void OnRecvMoveObjectMutableState(int id, MoveObjectMutableState msg)
    {

    }

    public void TryMoveToPos(float x, float z)
    {
        MoveToPos msg = new MoveToPos();
        msg.Pos = new PBVector2();
        msg.Pos.X = x;
        msg.Pos.Y = z;
        App.my.gameNetwork.Send(ProtoId.PidMoveToPos, msg);
    }

    public void TryStopMove()
    {
        App.my.gameNetwork.Send(ProtoId.PidStopMove);
    }

    // void RspFreeHero(int id, RspFreeHero msg)
}
