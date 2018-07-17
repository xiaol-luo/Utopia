using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System;

namespace Utopia.Logic
{
    public class LogicMgr
    {
        LogicBase[] m_modules = new LogicBase[(int)ELogicName.Count];
        Dictionary<Type, LogicBase> m_moduleMap = new Dictionary<Type, LogicBase>();

        public LogicMgr()
        {
            this.AddModuleHelper<SelectHero>();
        }

        protected void AddModuleHelper<T>() where T : LogicBase, new()
        {
            T module = new T();
            ELogicName moduleName = module.GetModuleName();
            Core.instance.log.LogAssert(null == m_modules[(int)moduleName], "Repeated Module {0}", moduleName);
            m_modules[(int)moduleName] = module;
            m_moduleMap.Add(typeof(T), module);
        }

        public void Init()
        {
            foreach (LogicBase module in m_modules)
            {
                module.Init();
            }
        }

        public void Awake()
        {
            foreach (LogicBase module in m_modules)
            {
                module.Awake();
            }
        }

        public void Release()
        {
            foreach (LogicBase module in m_modules)
            {
                module.Release();
            }
        }

        public LogicBase GetModule(ELogicName moduleName)
        {
            LogicBase ret = m_modules[(int)moduleName];
            return ret;
        }

        public T GetModule<T>() where T : LogicBase
        {
            LogicBase ret = null;
            m_moduleMap.TryGetValue(typeof(T), out ret);
            return ret as T;
        }
    }
}
