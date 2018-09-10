using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public class SuBullet : SuMissile
    {
        public SuBullet(SceneUnit _su) : base(_su)
        {
        }
        public override void InitSu(SceneUnitState msg)
        {
            m_evProxy.Subscribe<BulletState>(SuEventDef.MsgBulletState, OnMsgBulletState);
            m_evProxy.Subscribe<BulletTargetPos>(SuEventDef.MsgBulletTargetPos, OnMsgBulletTargetPos);
        }

        float m_moveSpeed;
        Vector3 m_targetPos;
        Vector3 m_velocity;
        float m_moveLastSec = 0.0f;
        int m_state = -1;

        void OnMsgBulletState(string evName, NetProto.BulletState msg)
        {
            Vector3 unitPos = new Vector3(msg.UnitPos.X, 0, msg.UnitPos.Z);
            Vector3 targetPos = new Vector3(msg.TargetPos.X, msg.TargetPos.Y, msg.TargetPos.Z);
            this.DoMove();
            m_state = msg.CurrState;
            m_moveLastSec = su.scene.nowSec;
            this.MakeMovePlan(msg.NowMs, unitPos, targetPos, msg.Speed);
        }
        void OnMsgBulletTargetPos(string evName, NetProto.BulletTargetPos msg)
        {
            Vector3 unitPos = new Vector3(msg.UnitPos.X, 0, msg.UnitPos.Z);
            Vector3 targetPos = new Vector3(msg.TargetPos.X, msg.TargetPos.Y, msg.TargetPos.Z);
            this.DoMove();
            this.MakeMovePlan(msg.NowMs, unitPos, targetPos, m_moveSpeed);
        }

        void MakeMovePlan(long nowMs, Vector3 unitPos, Vector3 targetPos, float moveSpeed)
        {
            this.CheckResetSuPos(unitPos, nowMs);
            m_moveSpeed = moveSpeed;
            m_targetPos = targetPos;
            Vector3 moveDir = m_targetPos - su.pos; moveDir.y = 0;
            m_velocity = moveDir.normalized * m_moveSpeed;
        }

        enum MoveState
        {
            None = 0,
            Ready,
            Moving,
            Done,
            Destroying,
            AllFinish,
        }

        void DoMove()
        {
            if ((int)MoveState.Moving != m_state)
                return;

            float deltaSec = su.scene.nowSec - m_moveLastSec;
            m_moveLastSec = su.scene.nowSec;
            Vector3 retPos = m_su.pos + m_velocity * deltaSec;
            m_su.pos = retPos;
            m_su.faceDir = Vector3.SignedAngle(Vector3.forward, m_velocity, Vector3.up);
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
            }
            return ret;
        }

        public override void Update()
        {
            this.DoMove();
        }
    }
}
