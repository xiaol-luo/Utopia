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
            so.AddModule(new SuMove(so));
            return so;
        }
    }
}
