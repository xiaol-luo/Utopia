using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    public class SuMissile : SceneUnitModule
    {
        public override ESuModule ModuleName()
        {
            return ESuModule.Missile;
        }
        public SuMissile(SceneUnit _su) : base(_su)
        {
        }
    }
}
