using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public class BulletActions : SuActions
    {
        public BulletActions(SceneUnit _su) : base(_su)
        {
        }

        public override void InitSu(SceneUnitState msg)
        {
            base.InitSu(msg);
        }

        public override void PlayAni(int aniName, float lastSec, float speedFactor, EAniNotBreakReason notBreakReason, int exclusiveGroupFlag)
        {
            
        }

        public override void StopAni(int aniName, int excludeGroupFlag)
        {

        }
    }
}
