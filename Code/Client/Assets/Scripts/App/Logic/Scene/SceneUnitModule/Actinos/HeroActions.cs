using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public enum EHeroAction
    {
        Idle = 0,
        Run,
        Attack1,
        Attack2,
        Attack3,
        Skill1,
        Skill2,
        Skill3,
        Dizzy,
        ForceMove,

        Count,
    }

    public class HeroActions : SuActions
    {
        public HeroActions(SceneUnit _su) : base(_su)
        {
        }

        protected HeroActionData[] m_actionDatas = new HeroActionData[(int)EHeroAction.Count];
        HeroActionData m_usingData = null;

        public override void InitSu(SceneUnitState msg)
        {
            base.InitSu(msg);
            for (int i = 0; i < m_actionDatas.Length; ++ i)
            {
                HeroActionData data = new HeroActionData();
                data.setting = settings[i];
                m_actionDatas[i] = data;
            }
        }

        public override void PlayAni(int aniName, float lastSec, float speedFactor, EAniNotBreakReason notBreakReason, int exclusiveGroupFlag=0)
        {
            EHeroAction eAction = (EHeroAction)aniName;
            if (eAction < EHeroAction.Idle || eAction >= EHeroAction.Count)
                return;

            HeroActionData data = m_actionDatas[aniName];
            if (data == m_usingData)
            {
                if ( 0 != (notBreakReason & EAniNotBreakReason.SameAni))
                {
                    return;
                }
            }

            data.speedFactor = speedFactor;
            if (0 != data.setting.exclusiveGroupFlag || 0 != exclusiveGroupFlag)
            {
                foreach (HeroActionData elem in m_actionDatas)
                {
                    if (0 != (elem.setting.exclusiveGroupFlag & data.setting.exclusiveGroupFlag) ||
                        0 != (elem.setting.exclusiveGroupFlag & exclusiveGroupFlag))
                    {
                        elem.endSec = 0.0f;
                    }
                }
            }
            data.endSec = (lastSec >= 0 ? m_elaspeSec + lastSec : -1);

            if (m_usingData.IsEnd(m_elaspeSec) || m_usingData.setting.eAction <= data.setting.eAction)
            {
                this.PickAniToPlay();
            }
        }

        protected void PickAniToPlay()
        {
            HeroActionData oldUsingData = m_usingData;
            m_usingData = null;
            m_model.ani.Stop();
            HeroActionData pickedData = m_actionDatas[(int)EHeroAction.Idle];
            for (int i = (int)EHeroAction.Count - 1; i >= 0; -- i)
            {
                HeroActionData elem = m_actionDatas[i];
                if (!elem.IsEnd(m_elaspeSec))
                {
                    pickedData = m_actionDatas[i];
                    break;
                }
            }
            m_usingData = pickedData;
            
            foreach (AnimationState state in m_model.ani)
            {
                state.speed = m_usingData.speedFactor;
            }
            if (m_actionDatas[(int)EHeroAction.Idle] == oldUsingData && m_usingData == oldUsingData)
            {
                // do nothing
            }
            else
            {
                m_model.ani.Play(m_usingData.setting.aniName);
            }
        }

        public override void StopAni(int aniName, int exclusiveGroupFlag)
        {
            if (0 != exclusiveGroupFlag)
            {
                foreach (HeroActionData elem in m_actionDatas)
                {
                    if (0 != (exclusiveGroupFlag & elem.setting.exclusiveGroupFlag))
                    {
                        elem.endSec = 0.0f;
                    }
                }
            }

            bool needSelectAniToPlay = false;
            if (null == m_usingData || m_usingData.IsEnd(m_elaspeSec))
                needSelectAniToPlay = true;

            if (aniName >= 0 || aniName < (int)EHeroAction.Count)
            {
                HeroActionData data = m_actionDatas[aniName];
                data.endSec = 0.0f;
                if (data == m_usingData)
                {
                    needSelectAniToPlay = true;
                }
            }
            if (needSelectAniToPlay)
            {
                this.PickAniToPlay();
            }
        }

        public override void Awake()
        {
            base.Awake();
            this.PickAniToPlay();
        }

        public override void Update()
        {
            base.Update();
            if (null != m_usingData && m_usingData.IsEnd(m_elaspeSec))
            {
                this.PickAniToPlay();
            }
        }

        public class HeroActionData
        {
            public HeroActionSetting setting;
            public float speedFactor = 1.0f;
            public float endSec = 0.0f; // < 0：无限循环直到主动停止

            public bool IsEnd(float nowSec)
            {
                if (EHeroAction.Idle == setting.eAction)
                    return false;
                return endSec >= 0 && endSec <= nowSec;
            }
        }

        public const int ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG = 1 << 0;
        public const int MOVE_EXCLUSIVE_GROUP_FLAG = 1 << 1;

        public class HeroActionSetting
        {
            public EHeroAction eAction;
            public string aniName;
            public bool isLoop = false;
            public int exclusiveGroupFlag = 0; // 互斥组
        }

        protected static HeroActionSetting[] settings = new HeroActionSetting[(int)EHeroAction.Count]
        {
            new HeroActionSetting()
            {
                eAction = EHeroAction.Idle,
                aniName = "idle",
                isLoop = true,
                exclusiveGroupFlag = 0
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Run,
                aniName = "run",
                isLoop = true,
                exclusiveGroupFlag = MOVE_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Attack1,
                aniName = "attack1",
                isLoop = false,
                exclusiveGroupFlag = ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Attack2,
                aniName = "attack2",
                isLoop = false,
                exclusiveGroupFlag = ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Attack3,
                aniName = "attack3",
                isLoop = false,
                exclusiveGroupFlag = ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Skill1,
                aniName = "skill1",
                isLoop = false,
                exclusiveGroupFlag = ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Skill2,
                aniName = "skill2",
                isLoop = false,
                exclusiveGroupFlag = ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Skill3,
                aniName = "skill3",
                isLoop = false,
                exclusiveGroupFlag = ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.Dizzy,
                aniName = "knockUpBegin",
                isLoop = true,
                exclusiveGroupFlag = 0
            },
            new HeroActionSetting()
            {
                eAction = EHeroAction.ForceMove,
                aniName = "knockUpStill",
                isLoop = true,
                exclusiveGroupFlag = MOVE_EXCLUSIVE_GROUP_FLAG
            },
        };
    }
}
