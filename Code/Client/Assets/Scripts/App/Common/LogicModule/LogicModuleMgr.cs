using UnityEngine;
using UnityEditor;
using System.Collections.Generic;
using System;

namespace Utopia
{
    public class LogicModuleMgr
    {
        LogicModuleBase[] m_modules = new LogicModuleBase[(int)ELogicModule.Count];
        Dictionary<Type, LogicModuleBase> m_moduleMap = new Dictionary<Type, LogicModuleBase>();

        public LogicModuleMgr()
        {
            this.AddModuleHelper<SelectHeroModule>();
        }

        protected void AddModuleHelper<T>() where T : LogicModuleBase, new()
        {
            T module = new T();
            ELogicModule moduleName = module.GetModuleName();
            Core.instance.log.LogAssert(null == m_modules[(int)moduleName], "Repeated Module {0}", moduleName);
            m_modules[(int)moduleName] = module;
            m_moduleMap.Add(typeof(T), module);
        }

        public void Init()
        {
            foreach (LogicModuleBase module in m_modules)
            {
                module.Init();
            }
        }

        public void Awake()
        {
            foreach (LogicModuleBase module in m_modules)
            {
                module.Awake();
            }
        }

        public void Release()
        {
            foreach (LogicModuleBase module in m_modules)
            {
                module.Release();
            }
        }

        public LogicModuleBase GetModule(ELogicModule moduleName)
        {
            LogicModuleBase ret = m_modules[(int)moduleName];
            return ret;
        }

        public T GetModule<T>() where T : LogicModuleBase
        {
            LogicModuleBase ret = null;
            m_moduleMap.TryGetValue(typeof(T), out ret);
            return ret as T;
        }
    }
}
