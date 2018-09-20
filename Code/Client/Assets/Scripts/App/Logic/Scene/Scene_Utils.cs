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
                        so.AddModule(new HeroActions(so));
                        so.AddModule(new SuSkill(so));
                    }
                    break;
                case ESceneUnitType.Effect: // 暂且这么写
                    {
                        so.AddModule(new SuBullet(so));
                        so.AddModule(new BulletActions(so));
                    }
                    break;
            }
            
            return so;
        }
    }
}
