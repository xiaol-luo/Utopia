
using NetProto;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Scene
{
    Transform m_rootObstacles = null;
    public Transform rootSceneObejcts { get { return m_rootSceneObjects; } }
    Transform m_rootSceneObjects = null;

    SceneObjcet m_testSceneObject = null;

    public void EnterScene(string sceneName)
    {
        App.my.gameNetwork.Send(ProtoId.PidLoadSceneComplete);
        App.my.gameNetwork.Send(ProtoId.PidPullAllSceneInfo);

        App.my.gameNetwork.Add<AllSceneObjectState>((int)ProtoId.PidPullAllSceneInfo, OnPullAllSceneObject);
        App.my.gameNetwork.Add<SceneObjectState>((int)ProtoId.PidSceneObjectState, OnRecvSceneObjectState);
        App.my.gameNetwork.Add<MoveObjectState>((int)ProtoId.PidMoveObjectState, OnRecvMoveObjectState);
        App.my.gameNetwork.Add<MoveObjectMutableState>((int)ProtoId.PidMoveObjectMutableState, OnRecvMoveObjectMutableState);

        {
            foreach (GameObject rootGo in SceneManager.GetActiveScene().GetRootGameObjects())
            {
                if (rootGo.name == "SceneObjects")
                {
                    m_rootSceneObjects = rootGo.transform;
                }
                if (rootGo.name == "Obstacles")
                {
                    m_rootObstacles = rootGo.transform;
                }
            }
        }

        {
            m_testSceneObject = new SceneObjcet(1, ESceneObject.Hero, 1);
            m_testSceneObject.position = Vector3.one;
        }
    }
    public void LeaveScene()
    {
        App.my.gameNetwork.Send(ProtoId.PidLeaveScene);
        m_testSceneObject = null;
        rootSceneObejcts.DetachChildren();
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
        if (null != m_testSceneObject)
        {
            m_testSceneObject.position = new Vector3(msg.Pos.X, msg.Pos.Y, msg.Pos.Z);
            if (msg.MoveAgentState == EMoveAgentState.MoveToPos ||
                msg.MoveAgentState == EMoveAgentState.MoveToDir)
            {
                Animation animation = m_testSceneObject.modelGo.GetComponent<Animation>();
                if (!animation.IsPlaying("run"))
                    animation.Play("run");
            }
            else if (msg.MoveAgentState == EMoveAgentState.ForceLine ||
                msg.MoveAgentState == EMoveAgentState.ForcePos)
            {
                Animation animation = m_testSceneObject.modelGo.GetComponent<Animation>();
                if (!animation.IsPlaying("knockUpStill"))
                    animation.Play("knockUpStill");
            }
            else
            {
                Animation animation = m_testSceneObject.modelGo.GetComponent<Animation>();
                if (!animation.IsPlaying("idle"))
                    animation.Play("idle");
            }

            m_testSceneObject.modelGo.transform.localRotation = Quaternion.AngleAxis(msg.Rotation, Vector3.up);
        }
        
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
    public void Update()
    {
        // Random rand = new Random();
        // App.my.scene.TryMoveToPos(rand.Next() % 100, rand.Next() % 100);

        this.CheckPlayerInput();
    }

    void CheckPlayerInput()
    {
        const int Mouse_Left_Click = 0;
        const int Mouse_Right_Click = 1;

        if (Input.GetMouseButtonDown(Mouse_Right_Click))
        {
            Vector3 hitGound = Vector3.zero;
            bool isOk = SceneUtils.ScreenToGround(Camera.main, Input.mousePosition, ref hitGound);
            if (isOk)
            {
                this.TryMoveToPos(hitGound.x, hitGound.z);
            }
        }
    }
    
    // void RspFreeHero(int id, RspFreeHero msg)
}
