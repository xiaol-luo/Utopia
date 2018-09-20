using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetProto;
using UnityEngine;
using SharpNav;

namespace Utopia
{
    public class SuMove : SceneUnitModule
    {
        public override ESuModule ModuleName()
        {
            return ESuModule.Move;
        }
        public SuMove(SceneUnit _su) : base(_su)
        {

        }

        SuActions m_suActions;

        public override void InitSu(SceneUnitState msg)
        {
            m_suActions = m_su.GetModule<SuActions>();
            m_evProxy.Subscribe<SceneUnitMove>(SuEventDef.MsgSceneUnitMove, OnMsgSceneUnitMove);
        }

        struct Orders
        {
            public const int Pre = 0;
            public const int curr = 1;
            public const int count = 2;
        }

        SceneUnitMove[] m_moveMsgs = new SceneUnitMove[Orders.count];
        SceneUnitTransform[] m_tranMsgs = new SceneUnitTransform[Orders.count];

        List<Vector3> m_movePoints = new List<Vector3>();
        int m_movePointsIdx = 0;
        EMoveAgentState m_moveState = EMoveAgentState.Idle;
        float m_moveSpeed = 0.0f;
        float m_moveSpeedFactor = 1.0f;
        float m_moveLastSec = 0.0f;

        void OnMsgSceneUnitMove(string evName, SceneUnitMove msg)
        {
            m_moveMsgs[Orders.Pre] = m_moveMsgs[Orders.curr];
            if (null == m_moveMsgs[Orders.Pre])
                m_moveMsgs[Orders.Pre] = msg;

            Scene scene = m_su.scene;
            NavMeshQuery navQuery = m_su.scene.navQuery;
            TiledNavMesh navMesh = m_su.scene.navMesh;
            long nowMs = scene.nowMs;
            float nowSec = m_su.scene.nowSec;
            Vector3 start = new Vector3(msg.UnitPos.X, 0, msg.UnitPos.Z);
            
            this.DoAllMove();
            CheckResetSuPos(start, msg.NowMs);

            m_moveState = msg.MoveAgentState;
            m_moveSpeed = msg.MaxMoveSpeed;

            EHeroAction aniName = EHeroAction.Idle;
            switch (msg.MoveAgentState)
            {
                case EMoveAgentState.MoveToPos:
                    {
                        aniName = EHeroAction.Run;
                        Vector3 end = new Vector3(msg.MoveDesiredPos.X, 0, msg.MoveDesiredPos.Y);
                        this.MakeMoveToPosPlan(start, end, msg.NowMs);
                        m_moveLastSec = nowSec;
                    }
                    break;
                case EMoveAgentState.MoveToDir:
                    {
                        aniName = EHeroAction.Run;
                    }
                    break;
                case EMoveAgentState.ForceLine:
                    {
                        aniName = EHeroAction.ForceMove;
                        Vector3 end = new Vector3(msg.ForceLineEndPos.X, 0, msg.ForceLineEndPos.Y);
                        Vector2 v = new Vector2(msg.ForceLineVelocity.X, msg.ForceLineVelocity.Y);
                        MakeForceLinePlan(start, end, v, msg.ForceLineTotalSec, msg.ForceLineElaspedSec, msg.NowMs);
                        m_forceLineStartSec = nowSec;
                        if (m_forceLineReached)
                        {
                            m_su.pos = m_forceLineEndPos;
                        }
                    }
                    break;
                case EMoveAgentState.ForcePos:
                    {
                        Vector3 end = new Vector3(msg.ForcePosDestination.X, 0, msg.ForcePosDestination.Y);
                        MakeForcePosPlan(start, end, msg.ForcePosSpeed, msg.NowMs);
                        m_forcePosLastSec = nowSec;
                        aniName = EHeroAction.ForceMove;
                    }
                    break;
            }

            m_suActions.PlayAni((int)aniName, -1, 1, EAniNotBreakReason.SameAni, HeroActions.MOVE_EXCLUSIVE_GROUP_FLAG);
        }

        void MakeMoveToPosPlan(Vector3 start, Vector3 end, long srvMs)
        {
            m_moveSpeedFactor = 1.0f;

            m_movePoints = m_su.scene.FindPath(start, end);
            if (null == m_movePoints || m_movePoints.Count <= 0)
            {
                m_movePoints = new List<Vector3>();
                m_movePoints.Add(start);
            }
            m_movePointsIdx = 0;
            if (m_movePoints.Count >= 2)
            {
                double d1 = (m_movePoints[1] - m_movePoints[0]).magnitude;
                double d2 = (m_movePoints[1] - m_su.pos).magnitude;
                double clientExtraDist = d2 - d1;
                double pathDist = 0.0f;
                for (int i = m_movePoints.Count - 1; i > 0; --i)
                {
                    pathDist += (m_movePoints[i] - m_movePoints[i - 1]).magnitude;
                }
                if (pathDist > 0)
                {
                    double factor = (clientExtraDist + pathDist) / pathDist;
                    m_moveSpeedFactor = (float)factor;
                    m_movePoints[0] = m_su.pos;
                }

                Core.instance.log.LogInfo("d1:{0}, d2:{1}, clientExtraDist:{2}, pathDist:{3}, factor{4}",
                    d1, d2, clientExtraDist, pathDist, m_moveSpeedFactor);
            }
            if (m_moveSpeedFactor > 1.1f)
                m_moveSpeedFactor = 1.1f;
            if (m_moveSpeedFactor < 0.9f)
                m_moveSpeedFactor = 0.9f;
            m_moveSpeedFactor = MakeInRange(m_moveSpeedFactor, 0.9f, 1.1f);
        }

        T MakeInRange<T>(T val, T minVal, T maxVal) where T : IComparable
        {
            T ret = val;
            if (minVal.CompareTo(maxVal) > 0)
            {
                T tmp = maxVal;
                maxVal = minVal;
                minVal = tmp;
            }
            if (ret.CompareTo(minVal) < 0)
                ret = minVal;
            if (ret.CompareTo(maxVal) > 0)
                ret = maxVal;
            return ret;
        }

        bool m_forceLineReached = true;
        Vector3 m_forceLineStartPos;
        Vector3 m_forceLineEndPos;
        Vector3 m_forceLineVelocity;
        float m_forceLineTotalSec = 0;
        float m_forceLineStartSec = 0;
        float m_forceLineVelocityFactor = 1.0f;
        void MakeForceLinePlan(Vector3 start, Vector3 end, Vector2 v, float totalSec, float elaspeSec, long srvMs)
        {
            float nowSce = m_su.scene.nowSec;
            m_forceLineVelocityFactor = 1.0f;
            Vector3 moved = v * elaspeSec;
            Vector3 srvPos = start + moved;
            Vector3 srvDelta = end - srvPos;
            Vector3 clientDelta = end - m_su.pos;
            float srvDeltaDist = srvDelta.magnitude;
            float clientDeltaDist = clientDelta.magnitude;
            if (srvDeltaDist > 0)
            {
                m_moveSpeedFactor = clientDeltaDist / srvDeltaDist;
                m_moveSpeedFactor = MakeInRange(m_moveSpeedFactor, 0.9f, 1.1f);
            }

            m_forceLineReached = CalPointReachedOrCross(end, start, srvPos);
            m_forceLineStartPos = m_su.pos;
            m_forceLineEndPos = end;
            {

                Vector3 tmp = (m_forceLineEndPos - m_forceLineStartPos);
                tmp.y = 0;
                m_forceLineVelocity = tmp.normalized * v.magnitude;
            }
            m_forceLineTotalSec = totalSec - elaspeSec;
        }

        bool m_forcePosReached = false;
        Vector3 m_forcePosDest;
        float m_forcePosSpeed;
        float m_forcePosSpeedFactor = 1.0f;
        float m_forcePosLastSec = 0;

        void MakeForcePosPlan(Vector3 start, Vector3 end, float speed, long srvMs)
        {
            m_forcePosReached = false;

            Vector3 srvDelta = end - start; srvDelta.y = 0;
            Vector3 clientDelta = end - m_su.pos; clientDelta.y = 0;

            float srvDeltaDist = srvDelta.magnitude;
            float clientDeltaDist = clientDelta.magnitude;
            if (srvDeltaDist <= 0 || clientDeltaDist <= 0)
                m_forcePosReached = true;
            m_forcePosSpeedFactor = clientDeltaDist / srvDeltaDist;
            m_forcePosSpeedFactor = MakeInRange(m_forcePosSpeedFactor, 0.9f, 1.1f);
            m_forcePosSpeed = speed;
            m_forcePosDest = end;
        }

        bool CalPointReachedOrCross(Vector3 end, Vector3 start, Vector3 nowPos)
        {
            bool ret = false;
            {
                Vector3 endToSrvPos = end - nowPos;
                Vector3 startToEnd = end - start;
                if (startToEnd.sqrMagnitude <= 0)
                {
                    ret = true;
                }
                if (endToSrvPos.sqrMagnitude <= 0)
                {
                    ret = true;
                }
                if (Vector3.Dot(endToSrvPos.normalized, startToEnd.normalized) < 0) // 夹角小于90度，srvPos越过了end
                {
                    ret = true;
                }
            }
            return ret;
        }

        public void HandleMsgSceneUnitTransform(SceneUnitTransform msg)
        {
            m_tranMsgs[Orders.Pre] = m_tranMsgs[Orders.curr];
            if (null == m_tranMsgs[Orders.Pre])
                m_tranMsgs[Orders.Pre] = msg;

            Vector3 msgPos = new Vector3(msg.Pos.X, msg.Pos.Y, msg.Pos.Z);
            Vector3 delta = m_su.pos - msgPos;

            switch (m_moveState)
            {
                case EMoveAgentState.MoveToPos:
                    {
                        if (CheckResetSuPos(msgPos, msg.Ms))
                        {
                            if (m_movePoints.Count > 0)
                            {
                                this.MakeMoveToPosPlan(m_su.pos, m_movePoints[m_movePoints.Count - 1], msg.Ms);
                                m_moveLastSec = m_su.scene.nowSec;
                            }
                        }
                    }
                    break;
                case EMoveAgentState.ForceLine:
                    {
                        if (CheckResetSuPos(msgPos, msg.Ms))
                        {
                            float elaspeSec = m_su.scene.nowSec - m_forceLineStartSec;
                            this.MakeForceLinePlan(m_su.pos, m_forceLineEndPos, m_forceLineVelocity, m_forceLineTotalSec, elaspeSec, msg.Ms);
                            m_forceLineStartSec = m_su.scene.nowSec;
                        }
                    }
                    break;
                default:
                    {

                        // m_su.SetPos(msg.Pos);
                        this.CheckResetSuPos(msgPos, msg.Ms);
                        m_su.faceDir = msg.FaceDir;
                    }
                    break;
            }
        }
        bool CheckResetSuPos(Vector3 dest, long ms)
        {
            bool ret = false;
            Vector3 delta = dest - m_su.pos;
            delta.y = 0;
            long deltaMs = ms - m_su.scene.nowMs;
            double timeDeltaDist = m_moveSpeed * deltaMs * 1.0 / Utopia.Scene.MsPerSec;
            double deltaDist = delta.magnitude + timeDeltaDist;
            if (deltaDist > 2.0f)
            {
                m_su.SetPos(dest);
                ret = true;
                Core.instance.log.LogWarning("CheckResetSuPos true deltaDist {0}, pos:{1} , factor {2}, ", deltaDist, dest, m_moveSpeedFactor);
            }
            return ret;
        }

        void DoMoveToPos()
        {
            if (EMoveAgentState.MoveToPos != m_moveState)
                return;

            float nowSec = m_su.scene.nowSec;
            float deltaSec = nowSec - m_moveLastSec;
            m_moveLastSec = nowSec;
            float moveDist = deltaSec * m_moveSpeed * m_moveSpeedFactor;
            if (moveDist > 0 && m_movePointsIdx < m_movePoints.Count)
            {
                Vector3 retPos = m_su.pos;
                Vector3 retFaceDir = m_movePoints[m_movePointsIdx] - m_su.pos;
                while (m_movePointsIdx < m_movePoints.Count && moveDist > 0)
                {
                    Vector3 moveTarget = m_movePoints[m_movePointsIdx];
                    Vector3 delta = moveTarget - retPos;
                    float deltaDist = delta.magnitude;
                    if (moveDist >= deltaDist)
                    {
                        ++m_movePointsIdx;
                        moveDist -= deltaDist;
                        retPos = moveTarget;
                    }
                    else
                    {
                        retPos = retPos + delta.normalized * moveDist;
                        moveDist = 0;
                    }
                    if (deltaDist > 0)
                    {
                        retFaceDir = delta;
                    }
                }
                m_su.pos = retPos;
                retFaceDir.y = 0;
                m_su.faceDir = Vector3.SignedAngle(Vector3.forward, retFaceDir, Vector3.up);
            }
        }

        void DoMoveForceLine()
        {
            if (EMoveAgentState.ForceLine != m_moveState)
                return;

            if (m_forceLineReached)
                return;

            float nowSec = m_su.scene.nowSec;
            float deltaSec = nowSec - m_forceLineStartSec;
            Vector3 toPos = m_forceLineStartPos + m_forceLineVelocity * deltaSec * m_forceLineVelocityFactor;

            bool isEnd = CalPointReachedOrCross(m_forceLineEndPos, m_forceLineStartPos, toPos);
            if (isEnd)
            {
                m_forceLineReached = true;
                toPos = m_forceLineEndPos;
            }
            m_su.pos = toPos;
        }

        void DoMoveForcePos()
        {
            if (EMoveAgentState.ForcePos != m_moveState)
                return;
            if (m_forcePosReached)
                return;

            float nowSec = m_su.scene.nowSec;
            float deltaSec = nowSec - m_forcePosLastSec;
            m_forcePosLastSec = nowSec;
            Vector3 moveDir = m_forcePosDest - m_su.pos; moveDir.y = 0;
            Vector3 retPos = m_su.pos + moveDir.normalized * deltaSec;

            bool ret = CalPointReachedOrCross(m_forcePosDest, m_su.pos, retPos);
            if (ret)
            {
                retPos = m_forcePosDest;
                m_forcePosReached = true;
            }
        }

        void DoAllMove()
        {
            this.DoMoveToPos();
            this.DoMoveForceLine();
            this.DoMoveForcePos();
        }

        public override void Update()
        {
            this.DoAllMove();
        }
    }
}
