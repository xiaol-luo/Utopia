using NetProto;
using UnityEngine;
using Utopia;

namespace Utopia
{
    public partial class Scene
    {
        protected SceneUnit BuildSceneUnit(SceneUnitState msg)
        {
            SceneUnit so = new SceneUnit(this);
            switch (msg.UnitType)
            {
                case ESceneUnitType.Hero:
                case ESceneUnitType.Monster:
                case ESceneUnitType.Soldier:
                    {
                        so.AddModule(new SuMove(so));
                    }
                    break;
                case ESceneUnitType.Effect: // 暂且这么写
                    {
                        so.AddModule(new SuBullet(so));
                    }
                    break;
            }
            
            return so;
        }
    }
}
