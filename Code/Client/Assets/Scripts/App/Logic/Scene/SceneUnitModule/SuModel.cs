using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public class SuModel : SceneUnitModule
    {
        public override ESuModule ModuleName()
        {
            return ESuModule.Model;
        }
        public SuModel(SceneUnit _su) : base(_su)
        {
        }

        Animation m_ani;
        public override void InitSu(SceneUnitState msg)
        {
            GameObject modelGo = null;
            {
                ResourceObserver resOb = null;
                {
                    if (ESceneUnitType.Effect == su.unitType)
                    {
                        resOb = m_su.resLoader.LoadAsset("Assets/Resources/Effect/Missile/GuidedMissile.prefab");
                    }
                    else
                    {
                        resOb = m_su.resLoader.LoadAsset("Assets/Resources/Heros/xiaoqiao_blue.prefab");
                    }
                }
                if (resOb.isLoaded)
                {
                    modelGo = resOb.Instantiate<GameObject>();
                }
                else
                {
                    modelGo = new GameObject();
                }
            }

            modelGo.name = "model";
            modelGo.transform.SetParent(m_su.transform);
            m_ani = modelGo.GetComponent<Animation>();
            evProxy.Subscribe<SceneUnitSkillAction>(SuEventDef.MsgSceneUnitSkillAction, OnMsgSceneUnitSkillAction);
        }
        public enum EAniNotBreakReason
        {
            None = 0,
            Playing = 1 << 0,
            SameAni = 1 << 1,
        }

        public void PlayAni(string aniName, EAniNotBreakReason notBreakFlag)
        {
            PlayAni(aniName, (int)notBreakFlag);
        }
        public void PlayAni(string aniName, int notBreakFlag)
        {
            bool isNotBreak = false;
            if (0 != (notBreakFlag & (int)EAniNotBreakReason.Playing))
            {
                if (m_ani.isPlaying)
                {
                    isNotBreak = true;
                }
            }
            if (0 != (notBreakFlag & (int)EAniNotBreakReason.SameAni))
            {
                if (m_ani.IsPlaying(aniName))
                {
                    isNotBreak = true;
                }
            }
            if (!isNotBreak)
            {
                m_ani.Play(aniName);
            }
        }

        void OnMsgSceneUnitSkillAction(string evName, SceneUnitSkillAction msg)
        {
            switch(msg.Stage)
            {
                case ESkillState.EssPreparing:
                    {
                        this.PlayAni("skill1", SuModel.EAniNotBreakReason.None);
                    }
                    break;
                case ESkillState.EssReleasing:
                    {
                        this.PlayAni("skill2", SuModel.EAniNotBreakReason.None);
                    }
                    break;
                case ESkillState.EssLasting:
                    {
                        this.PlayAni("skill3", SuModel.EAniNotBreakReason.None);
                    }
                    break;
            }
        }
    }
}
