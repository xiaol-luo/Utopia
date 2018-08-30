using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetProto;
using UnityEngine;

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

        public override void InitSu(SceneUnitState msg)
        {
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

        void OnMsgSceneUnitMove(string evName, SceneUnitMove msg)
        {
            m_moveMsgs[Orders.Pre] = m_moveMsgs[Orders.curr];
            if (null == m_moveMsgs[Orders.Pre])
                m_moveMsgs[Orders.Pre] = msg;

            if (m_su.IsPlayingSkill())
                return;

            string aniName = "idle";
            switch (msg.MoveAgentState)
            {
                case EMoveAgentState.MoveToPos:
                case EMoveAgentState.MoveToDir:
                    {
                        aniName = "run";
                    }
                    break;
                case EMoveAgentState.ForceLine:
                case EMoveAgentState.ForcePos:
                    {
                        aniName = "knockUpStill";
                    }
                    break;
            }
            m_su.model.PlayAni(aniName, SuModel.EAniNotBreakReason.SameAni);
        }
        public void HandleMsgSceneUnitTransform(SceneUnitTransform msg)
        {
            m_tranMsgs[Orders.Pre] = m_tranMsgs[Orders.curr];
            if (null == m_tranMsgs[Orders.Pre])
                m_tranMsgs[Orders.Pre] = msg;

            m_su.SetPos(msg.Pos);
            m_su.faceDir = msg.FaceDir;
        }

        public override void Update()
        {
            
        }
    }
}
