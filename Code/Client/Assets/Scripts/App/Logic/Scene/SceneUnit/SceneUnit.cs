
using NetProto;
using UnityEngine;
using Utopia;
using System.Collections.Generic;

namespace Utopia
{
    public class SceneUnit
    {
        Dictionary<ESuModule, SceneUnitModule> m_modules = new Dictionary<ESuModule, SceneUnitModule>();
        public Transform transform { get { return m_root.transform; } }
        SuModel m_suModel;
        public SuModel model { get { return m_suModel; } }
        GameObject m_root;
        public GameObject root { get { return m_root; } }
        Scene m_scene;
        public Scene scene { get { return m_scene; } }

        ResourceLoaderProxy m_resLoader;
        public ResourceLoaderProxy resLoader { get { return m_resLoader; } }

        EventMgr<string> m_evMgr;
        public EventMgr<string> evMgr { get { return m_evMgr; } }

        public SceneUnit(Scene scene)
        {
            m_scene = scene;
            m_resLoader = ResourceLoaderProxy.Create();
            m_evMgr = new EventMgr<string>();

            m_suModel = new SuModel(this);
            this.AddModule(m_suModel);
        }

        public void Init(SceneUnitState msg)
        {
            unitId = msg.SuId;
            unitType = msg.UnitType;

            m_root = new GameObject();
            m_root.name = string.Format("{0}_{1}", unitType, unitId);
            m_root.transform.SetParent(scene.rootSceneObejcts);

            foreach (var module in m_modules.Values)
            {
                module.InitSu(msg);
            }

            evMgr.Subscribe<SceneUnitTransform>(SuEventDef.MsgSceneUnitTransform, OnMsgSceneUnitTransform);
        }

        public void Awake()
        {
            foreach (var module in m_modules.Values)
            {
                module.Awake();
            }
        }

        public void Update()
        {
            foreach (var module in m_modules.Values)
            {
                module.Update();
            }
        }

        public void Release()
        {
            foreach (var module in m_modules.Values)
            {
                module.Release();
            }
            m_modules.Clear();
            GameObject.Destroy(m_root);
            m_resLoader.Release();
            m_evMgr.ClearAll();
        }

        public bool AddModule(SceneUnitModule module)
        {
            ESuModule moduleName = module.ModuleName();
            SceneUnitModule ret = this.GetModuleByName(moduleName);
            if (null != ret)
                return false;
            m_modules.Add(moduleName, module);
            return true;
        }
        SceneUnitModule GetModuleByName(ESuModule name)
        {
            SceneUnitModule ret = null;
            m_modules.TryGetValue(name, out ret);
            return ret;
        }

        public T GetModule<T>() where T : SceneUnitModule 
        {
            T ret = null;
            foreach (var module in m_modules.Values)
            {
                ret = module as T;
                if (null != ret)
                    break;
            }
            return ret;
        }

        public ulong unitId { get; protected set; }
        public int unitType { get; protected set; }
        public int skillId { get; set; }
        public ESkillState skillStage { get; set; }

        public bool IsPlayingSkill()
        {
            return skillId != 0 && ESkillState.EssEnd != skillStage;
        }
        float m_faceDir = 0.0f;
        public float faceDir {
            get { return m_faceDir; }
            set
            {
                m_faceDir = value;
                this.transform.localRotation = Quaternion.AngleAxis(m_faceDir, Vector3.up);
                // Quaternion.Angle(this.transform.rotation.eulerAngles)
            }
        }
        public Vector3 pos
        {
            get { return this.transform.localPosition; }
            set { this.transform.localPosition = value; }
        }
        public void SetPos(NetProto.PBVector3 value)
        {
            pos = new Vector3(value.X, value.Y, value.Z);
        }
        public void SetPos(Vector3 value)
        {
            pos = value;
        }

        void OnMsgSceneUnitTransform(string evName, SceneUnitTransform msg)
        {
            {
                SuMove module = this.GetModule<SuMove>();
                if (null != module)
                {
                    module.HandleMsgSceneUnitTransform(msg);
                    return;
                }
            }

            this.SetPos(msg.Pos);
            this.faceDir = msg.FaceDir;
        }
    }
}


