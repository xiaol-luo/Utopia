using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.EventSystems;

namespace Utopia
{
    public partial class Scene
    {
        void Su_OnSceneLoaded()
        {
            App.instance.net.gameSrv.Add<SceneUnitState>(PID.SceneUnitState, OnRecvSceneUnitState);
            App.instance.net.gameSrv.Add<SceneUnitTransform>(PID.SceneUnitTransform, OnRecvSceneUnitTransform);
            App.instance.net.gameSrv.Add<SceneUnitMove>(PID.SceneUnitMove, OnRecvceneUnitMove);
            App.instance.net.gameSrv.Add<SceneObjectDisappear>(PID.SceneObjectDisappear, OnSceneObjectDisappear);
            App.instance.net.gameSrv.Add<SceneUnitSkillAction>(PID.SceneUnitSkillAction, OnSceneUnitSkillAction);

            m_evProxy.Subscribe<PointerEventData>(SceneEventDef.MouseHitGround, OnMouseHitGround);
        }

        void Su_LeaveScene()
        {
            App.instance.net.gameSrv.Remove(PID.SceneUnitState);
            App.instance.net.gameSrv.Remove(PID.SceneUnitTransform);
            App.instance.net.gameSrv.Remove(PID.SceneUnitMove);
            App.instance.net.gameSrv.Remove(PID.SceneObjectDisappear);
            App.instance.net.gameSrv.Remove(PID.SceneUnitSkillAction);
        }

        Dictionary<ulong, SceneUnit> m_sceneUnits = new Dictionary<ulong, SceneUnit>();

        public SceneUnit mainHero
        {
            get
            {
                SceneUnit so;
                m_sceneUnits.TryGetValue(m_mainHeroId, out so);
                return so;
            }
        }

        ulong targetSuid
        {
            get
            {
                foreach (var kv_pair in m_sceneUnits)
                {
                    if (kv_pair.Key != mainHero.unitId && kv_pair.Value.unitType == mainHero.unitType)
                        return kv_pair.Key;
                }
                return 0;
            }
        }
        SceneUnit GetSceneObject(ulong objId)
        {
            SceneUnit so = null;
            m_sceneUnits.TryGetValue(objId, out so);
            return so;
        }

        void OnRecvSceneUnitState(int id, SceneUnitState msg)
        {
            SceneUnit so = this.GetSceneObject(msg.SuId);
            if (null == so)
            {
                so = BuildSceneUnit(msg);
                so.Init(msg);
                m_sceneUnits[so.unitId] = so;
                so.Awake();
            }
            so.SetPos(msg.Pos);
            so.faceDir = msg.FaceDir;
        }
        void OnRecvSceneUnitTransform(int id, SceneUnitTransform msg)
        {
            SceneUnit so = this.GetSceneObject(msg.SuId);
            if (null == so)
                return;

            so.evMgr.Fire(SuEventDef.MsgSceneUnitTransform, msg);
        }
        void OnRecvceneUnitMove(int id, SceneUnitMove msg)
        {
            SceneUnit so = this.GetSceneObject(msg.SuId);
            if (null == so)
                return;

            so.evMgr.Fire(SuEventDef.MsgSceneUnitMove, msg);
        }

        void OnSceneObjectDisappear(int id, SceneObjectDisappear msg)
        {
            foreach (ulong objid in msg.Objids)
            {
                SceneUnit obj = this.GetSceneObject(objid);
                if (null == obj)
                    continue;

                m_sceneUnits.Remove(objid);
                obj.Release();
            }
        }
        void OnSceneUnitSkillAction(int id, SceneUnitSkillAction msg)
        {
            SceneUnit so = this.GetSceneObject(msg.SuId);
            if (null == so)
                return;

            so.skillId = msg.SkillId;
            so.skillStage = msg.Stage;
            so.evMgr.Fire(SuEventDef.MsgSceneUnitSkillAction, msg);
        }
        public void TryStopMove()
        {
            App.instance.net.gameSrv.Send(PID.StopMove);
        }
        void CastSkill(ESkillSlot skillSlot, ulong targetId, Vector3 pos)
        {
            BattleOperation msg = new BattleOperation();
            msg.Opera = EPlayerOpera.EpoCastSkill;
            msg.TargetId = targetId;
            msg.Pos = new PBVector2() { X = pos.x, Y = pos.z };
            msg.SkillSlot = skillSlot;
            App.instance.net.gameSrv.Send(PID.BattleOperaReq, msg);
        }
        void TraceUnit(ulong targetId)
        {
            BattleOperation msg = new BattleOperation();
            msg.Opera = EPlayerOpera.EpoTrace;
            msg.TargetId = targetId;
            App.instance.net.gameSrv.Send(PID.BattleOperaReq, msg);
        }
        void TryMoveToPos(Vector3 pos)
        {
            BattleOperation msg = new BattleOperation();
            msg.Opera = EPlayerOpera.EpoMove;
            msg.Pos = new PBVector2() { X = pos.x, Y = pos.z };
            App.instance.net.gameSrv.Send(PID.BattleOperaReq, msg);
        }
        void StopAction()
        {
            BattleOperation msg = new BattleOperation();
            msg.Opera = EPlayerOpera.EpoStop;
            App.instance.net.gameSrv.Send(PID.BattleOperaReq, msg);
        }
        void OnMouseHitGround(string evName, PointerEventData evData)
        {
            Vector3 worldPos = evData.pointerCurrentRaycast.worldPosition;
            // Core.instance.log.LogDebug("Scene UPdate {0} {1} {2}", worldPos.x, worldPos.y, worldPos.z);

            if (PointerEventData.InputButton.Right == evData.button)
            {
                this.TryMoveToPos(worldPos);
            }
        }

        void UpdateSus()
        {
            List<SceneUnit> sus = new List<SceneUnit>(m_sceneUnits.Values);
            foreach (var su in sus)
            {
                su.Update();
            }
        }
    }
}