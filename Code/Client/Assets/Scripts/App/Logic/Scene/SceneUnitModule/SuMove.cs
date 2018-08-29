using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utopia
{
    public class SuMove : SceneUnitModule
    {
        public override ESuModule ModuleName()
        {
            return ESuModule.Move;
        }
        public SuMove(SceneUnit _su) : base(_su)
        {
        }
    }
}
