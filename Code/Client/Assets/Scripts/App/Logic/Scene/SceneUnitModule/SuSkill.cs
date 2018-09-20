using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public class SuSkill : SceneUnitModule
    {
        public override ESuModule ModuleName()
        {
            return ESuModule.Skill;
        }
        public SuSkill(SceneUnit _su) : base(_su)
        {
        }

        SuActions m_suActions;

        public override void InitSu(SceneUnitState msg)
        {
            m_suActions = m_su.GetModule<SuActions>();
            evProxy.Subscribe<SceneUnitSkillAction>(SuEventDef.MsgSceneUnitSkillAction, OnMsgSceneUnitSkillAction);
        }

        void OnMsgSceneUnitSkillAction(string evName, SceneUnitSkillAction msg)
        {
            switch(msg.Stage)
            {
                case ESkillState.EssPreparing:
                    {
                        m_suActions.PlayAni((int)EHeroAction.Skill1, 2, 1, EAniNotBreakReason.None, HeroActions.ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG);
                    }
                    break;
                case ESkillState.EssReleasing:
                    {
                        // m_suActions.PlayAni((int)EHeroAction.Skill2, 2, 1, EAniNotBreakReason.None, HeroActions.ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG);
                    }
                    break;
                case ESkillState.EssLasting:
                    {
                        // m_suActions.PlayAni((int)EHeroAction.Skill3, 2, 1, EAniNotBreakReason.None, HeroActions.ATTACK_SKILL_EXCLUSIVE_GROUP_FLAG);
                    }
                    break;
            }
        }
    }
}
