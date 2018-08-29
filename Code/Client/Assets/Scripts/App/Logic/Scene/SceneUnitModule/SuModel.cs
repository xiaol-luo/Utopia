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

        public override void InitSu(SceneUnitState msg)
        {
            GameObject modelGo = null;
            {
                ResourceObserver resOb = null;
                {
                    if (5 == su.unitType)
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

            }
        }
    }
}
