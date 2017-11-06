
using NetProto;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Scene
{
    Transform m_rootObstacles = null;
    public Transform rootSceneObejcts { get { return m_rootSceneObjects; } }
    Transform m_rootSceneObjects = null;

    Dictionary<ulong, SceneObjcet> m_sceneObjects = new Dictionary<ulong, SceneObjcet>();

    public void EnterScene(string sceneName)
    {
        App.my.gameNetwork.Send(ProtoId.PidLoadSceneComplete);
        App.my.gameNetwork.Send(ProtoId.PidPullAllSceneInfo);
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
    }
    public void LeaveScene()
    {
        App.my.gameNetwork.Send(ProtoId.PidLeaveScene);
        m_sceneObjects.Clear();
        rootSceneObejcts.DetachChildren();
    }
    
    SceneObjcet GetSceneObject(ulong objId)
    {
        SceneObjcet so = null;
        m_sceneObjects.TryGetValue(objId, out so);
        return so;
    }

    void OnRecvSceneObjectState(int id, SceneObjectState msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.Objid);
        if (null == so)
        {
            so = new SceneObjcet(msg.Objid, msg.ObjType, msg.ModelId);
            m_sceneObjects[so.id] = so;
        }
        so.SetPos(msg.Pos);
        so.faceDir = msg.Rotation;
    }

    void OnRecvMoveObjectState(int id, MoveObjectState msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.ObjState.Objid);
        if (null == so)
        {
            so = new SceneObjcet(msg.ObjState.Objid, msg.ObjState.ObjType, msg.ObjState.ModelId);
            m_sceneObjects[so.id] = so;
        }
        so.SetPos(msg.ObjState.Pos);
        so.faceDir = msg.ObjState.Rotation;

    }
    void OnRecvMoveObjectMutableState(int id, MoveObjectMutableState msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.Objid);
        if (null == so)
            return;

        so.SetPos(msg.Pos);
        so.faceDir = msg.Rotation;
        if (msg.MoveAgentState == EMoveAgentState.MoveToPos ||
                msg.MoveAgentState == EMoveAgentState.MoveToDir)
        {
            Animation animation = so.modelGo.GetComponent<Animation>();
            if (!animation.IsPlaying("run"))
                animation.Play("run");
        }
        else if (msg.MoveAgentState == EMoveAgentState.ForceLine ||
            msg.MoveAgentState == EMoveAgentState.ForcePos)
        {
            Animation animation = so.modelGo.GetComponent<Animation>();
            if (!animation.IsPlaying("knockUpStill"))
                animation.Play("knockUpStill");
        }
        else
        {
            Animation animation = so.modelGo.GetComponent<Animation>();
            if (!animation.IsPlaying("idle"))
                animation.Play("idle");
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
