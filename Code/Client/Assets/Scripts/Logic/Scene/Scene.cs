
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

    ulong targetSuid
    {
        get
        {
            foreach (var kv_pair in m_sceneObjects)
            {
                if (kv_pair.Key != mainHero.id)
                    return kv_pair.Key;
            }
            return 0;
        }
    }

    public void EnterScene(string sceneName)
    {
        m_vgg = ViewGridGizmos.GetViewGridGizmosFromScene();

        App.my.gameNetwork.Send(ProtoId.PidLoadSceneComplete);

        App.my.gameNetwork.Add<SceneUnitState>((int)ProtoId.PidSceneUnitState, OnRecvSceneUnitState);
        App.my.gameNetwork.Add<SceneUnitTransform>((int)ProtoId.PidSceneUnitTransform, OnRecvSceneUnitTransform);
        App.my.gameNetwork.Add<SceneUnitMove>((int)ProtoId.PidSceneUnitMove, OnRecvceneUnitMove);
        App.my.gameNetwork.Add<SceneObjectDisappear>((int)ProtoId.PidSceneObjectDisappear, OnSceneObjectDisappear);
        App.my.gameNetwork.Add<SceneUnitSkillAction>((int)ProtoId.PidSceneUnitSkillAction, OnSceneUnitSkillAction);

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

        App.my.gameNetwork.Remove((int)ProtoId.PidSceneUnitState);
        App.my.gameNetwork.Remove((int)ProtoId.PidSceneUnitTransform);
        App.my.gameNetwork.Remove((int)ProtoId.PidSceneUnitMove);
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

    void OnRecvSceneUnitState(int id, SceneUnitState msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.SuId);
        if (null == so)
        {
            so = new SceneObjcet(msg.SuId, msg.UnitType, msg.ModelId);
            m_sceneObjects[so.id] = so;
        }
        so.SetPos(msg.Pos);
        so.faceDir = msg.FaceDir;
    }
    void OnRecvSceneUnitTransform(int id, SceneUnitTransform msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.SuId);
        if (null == so)
            return;

        so.SetPos(msg.Pos);
        so.faceDir = msg.FaceDir;
    }
    void OnRecvceneUnitMove(int id, SceneUnitMove msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.SuId);
        if (null == so)
            return;

        if (so.IsPlayingSkill())
            return;

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
    void OnSceneUnitSkillAction(int id, SceneUnitSkillAction msg)
    {
        SceneObjcet so = this.GetSceneObject(msg.SuId);
        if (null == so) return;

        so.skillId = msg.SkillId;
        so.skillStage = msg.Stage;
        if (ESkillState.EssPreparing == msg.Stage)
        {
            Animation animation = so.modelGo.GetComponent<Animation>();
            animation.Play("skill1");
        }
        if (ESkillState.EssReleasing == msg.Stage)
        {
            Animation animation = so.modelGo.GetComponent<Animation>();
            animation.Play("skill2");
        }
        if (ESkillState.EssLasting == msg.Stage)
        {
            Animation animation = so.modelGo.GetComponent<Animation>();
            animation.Play("skill3");
        }
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
                this.TryMoveToPos(hitGound);
            }
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            this.StopAction();
        }
        
        if (Input.GetKeyDown(KeyCode.Q))
        {
            Vector3 hitGound = Vector3.zero;
            bool isOk = SceneUtils.ScreenToGround(Camera.main, Input.mousePosition, ref hitGound);
            if (isOk)
            {
                this.CastSkill(ESkillSlot.EssQslot, targetSuid, hitGound);
            }
        }
        if (Input.GetKeyDown(KeyCode.W))
        {
            Vector3 hitGound = Vector3.zero;
            bool isOk = SceneUtils.ScreenToGround(Camera.main, Input.mousePosition, ref hitGound);
            if (isOk)
            {
                this.CastSkill(ESkillSlot.EssWslot, targetSuid, hitGound);
            }
        }
        if (Input.GetKeyDown(KeyCode.F))
        {
            this.TraceUnit(targetSuid);
        }

    }
    void CastSkill(ESkillSlot skillSlot, ulong targetId, Vector3 pos)
    {
        BattleOperation msg = new BattleOperation();
        msg.Opera = EPlayerOpera.EpoCastSkill;
        msg.TargetId = targetId;
        msg.Pos = new PBVector2() { X = pos.x, Y = pos.z };
		msg.SkillSlot = skillSlot;
        App.my.gameNetwork.Send(ProtoId.PidBattleOperaReq, msg);
    }
    void TraceUnit(ulong targetId)
    {
        BattleOperation msg = new BattleOperation();
        msg.Opera = EPlayerOpera.EpoTrace;
        msg.TargetId = targetId;
        App.my.gameNetwork.Send(ProtoId.PidBattleOperaReq, msg);
    }
    void TryMoveToPos(Vector3 pos)
    {
        BattleOperation msg = new BattleOperation();
        msg.Opera = EPlayerOpera.EpoMove;
        msg.Pos = new PBVector2() { X = pos.x, Y = pos.z };
        App.my.gameNetwork.Send(ProtoId.PidBattleOperaReq, msg);
    }
    void StopAction()
    {
        BattleOperation msg = new BattleOperation();
        msg.Opera = EPlayerOpera.EpoStop;
        App.my.gameNetwork.Send(ProtoId.PidBattleOperaReq, msg);
    }

    // void RspFreeHero(int id, RspFreeHero msg)
}
