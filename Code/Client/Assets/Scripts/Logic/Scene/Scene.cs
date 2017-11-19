
using NetProto;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Scene
{
    ViewGridGizmos m_vgg = null;
    Transform m_rootObstacles = null;
    public Transform rootSceneObejcts { get { return m_rootSceneObjects; } }
    Transform m_rootSceneObjects = null;

    Dictionary<ulong, SceneObjcet> m_sceneObjects = new Dictionary<ulong, SceneObjcet>();
    public SceneObjcet mainHero
    {
        get
        {
            SceneObjcet so;
            m_sceneObjects.TryGetValue(App.my.heroId, out so);
            return so;
        }
    }

    public void EnterScene(string sceneName)
    {
        m_vgg = ViewGridGizmos.GetViewGridGizmosFromScene();

        App.my.gameNetwork.Send(ProtoId.PidLoadSceneComplete);
        App.my.gameNetwork.Send(ProtoId.PidPullAllSceneInfo);
        App.my.gameNetwork.Add<SceneObjectState>((int)ProtoId.PidSceneObjectState, OnRecvSceneObjectState);
        App.my.gameNetwork.Add<MoveObjectState>((int)ProtoId.PidMoveObjectState, OnRecvMoveObjectState);
        App.my.gameNetwork.Add<MoveObjectMutableState>((int)ProtoId.PidMoveObjectMutableState, OnRecvMoveObjectMutableState);
        App.my.gameNetwork.Add<SceneObjectDisappear>((int)ProtoId.PidSceneObjectDisappear, OnSceneObjectDisappear);
        App.my.gameNetwork.Add<ViewAllGrids>((int)ProtoId.PidViewAllGrids, (int id, ViewAllGrids msg) =>
        {
            m_vgg.SetAllGrids(msg);
        });
        App.my.gameNetwork.Add<ViewSnapshot>((int)ProtoId.PidViewSnapshot, (int id, ViewSnapshot msg) =>
        {
            m_vgg.SetSnapshot(msg);
        });
        App.my.gameNetwork.Add<ViewSnapshotDiff>((int)ProtoId.PidViewSnapshotDiff, (int id, ViewSnapshotDiff msg) =>
        {
            m_vgg.SetSnapshotDiff(msg);
        });


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

        App.my.gameNetwork.Remove((int)ProtoId.PidSceneObjectState);
        App.my.gameNetwork.Remove((int)ProtoId.PidMoveObjectState);
        App.my.gameNetwork.Remove((int)ProtoId.PidMoveObjectMutableState);
        App.my.gameNetwork.Remove((int)ProtoId.PidSceneObjectDisappear);
        App.my.gameNetwork.Remove((int)ProtoId.PidViewAllGrids);
        App.my.gameNetwork.Remove((int)ProtoId.PidViewSnapshot);
        App.my.gameNetwork.Remove((int)ProtoId.PidViewSnapshotDiff);
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

    void OnSceneObjectDisappear(int id, SceneObjectDisappear msg)
    {
        foreach (ulong objid in msg.Objids)
        {
            SceneObjcet obj = this.GetSceneObject(objid);
            if (null == obj)
                continue;
            m_sceneObjects.Remove(objid);
            GameObject.Destroy(obj.modelGo); 
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
                this.SendBattleOpera(EBattleOperation.EboMove, 0, hitGound);
            }
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            this.SendBattleOpera(EBattleOperation.EboStop);
        }
        if (Input.GetKeyDown(KeyCode.Q))
        {
            Vector3 hitGound = Vector3.zero;
            bool isOk = SceneUtils.ScreenToGround(Camera.main, Input.mousePosition, ref hitGound);
            if (isOk)
            {
                this.SendBattleOpera(EBattleOperation.EboCastSkillQ, 0, hitGound);
            }
        }
        if (Input.GetKeyDown(KeyCode.W))
        {
            Vector3 hitGound = Vector3.zero;
            bool isOk = SceneUtils.ScreenToGround(Camera.main, Input.mousePosition, ref hitGound);
            if (isOk)
            {
                this.SendBattleOpera(EBattleOperation.EboCastSkillW, 0, hitGound);
            }
        }
        if (Input.GetKeyDown(KeyCode.E))
        {
            this.SendBattleOpera(EBattleOperation.EboCastSkillE);
        }
    }

    void SendBattleOpera(EBattleOperation opera, ulong targetId, Vector3 pos)
    {
        BattleOperation msg = new BattleOperation();
        msg.Opera = opera;
        msg.TargetId = targetId;
        if (null != pos)
        {
            msg.Pos = new PBVector2() { X = pos.x, Y = pos.z };

            Vector3 tmp_dir = pos - mainHero.pos;
            msg.Dir = Vector2.SignedAngle(Vector2.up, new Vector2(tmp_dir.x, tmp_dir.z));
        }
        if (null != pos)
        {
        }
        App.my.gameNetwork.Send(ProtoId.PidBattleOperaReq, msg);
    }
    void SendBattleOpera(EBattleOperation opera)
    {
        this.SendBattleOpera(opera, 0, new Vector3());
    }
    void SendBattleOpera(EBattleOperation opera, ulong targetId)
    {
        this.SendBattleOpera(opera, targetId, new Vector3());
    }

    // void RspFreeHero(int id, RspFreeHero msg)
}
