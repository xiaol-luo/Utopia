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

        public Animation ani { get { return m_ani; } }

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
        }
    }
}
