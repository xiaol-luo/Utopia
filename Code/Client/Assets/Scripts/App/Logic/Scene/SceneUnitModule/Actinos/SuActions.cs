using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public enum EAniNotBreakReason
    {
        None = 0,
        SameAni = 1 << 0,
    }

    public class SuActions : SceneUnitModule
    {
        public override ESuModule ModuleName()
        {
            return ESuModule.Actions;
        }

        public SuActions(SceneUnit _su) : base(_su)
        {
        }

        protected SuModel m_model;
        protected bool m_isFreeze = false;
        protected float m_elaspeSec = 0.0f;

        public override void InitSu(SceneUnitState msg)
        {
            m_model = su.GetModule<SuModel>();
        }

        public virtual void PlayAni(int aniName, float lastSec, float speedFactor, EAniNotBreakReason notBreakReason, int exclusiveGroupFlag)
        {
            
        }

        public virtual void StopAni(int aniName, int excludeGroupFlag)
        {

        }

        public override void Update()
        {
            if (!m_isFreeze)
            {
                m_elaspeSec += Time.deltaTime;
            }
        }

        public virtual void Freeze()
        {
            if (m_isFreeze)
                return;

            m_isFreeze = true;
        }

        public virtual void CancelFreeze()
        {
            if (!m_isFreeze)
                return;

            m_isFreeze = false;
        }
    }
}
