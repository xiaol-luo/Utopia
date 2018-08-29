using NetProto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{

    public enum ESuModule
    {
        Model, // 模型
        Move, // 移动 
    }

    public class SceneUnitModule
    {
        public virtual ESuModule ModuleName()
        {
            throw (new NotImplementedException());
        }

        protected SceneUnit m_su;
        public SceneUnit su { get { return m_su; } }
        public SceneUnitModule(SceneUnit _su)
        {
            m_su = _su;
        }
        public virtual void InitSu(SceneUnitState msg)
        {

        }
        public virtual void Awake()
        {

        }
        public virtual void Release()
        {

        }
    }
}
