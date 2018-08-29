
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

        public SceneUnit(Scene scene)
        {
            m_scene = scene;
            m_resLoader = ResourceLoaderProxy.Create();

            m_root = new GameObject();
            m_root.name = string.Format("{0}_{1}", unitType, unitId);
            m_root.transform.SetParent(scene.rootSceneObejcts);

            m_suModel = new SuModel(this);
            this.AddModule(m_suModel);
        }

        public void Init(SceneUnitState msg)
        {
            unitId = msg.SuId;
            unitType = msg.UnitType;

            foreach (var module in m_modules.Values)
            {
                module.InitSu(msg);
            }
        }

        public void Awake()
        {
            foreach (var module in m_modules.Values)
            {
                module.Awake();
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
        }

        bool AddModule(SceneUnitModule module)
        {
            ESuModule moduleName = module.ModuleName();
            SceneUnitModule ret = this.GetModule(moduleName);
            if (null != ret)
                return false;
            m_modules.Add(moduleName, module);
            return true;
        }
        SceneUnitModule GetModule(ESuModule name)
        {
            SceneUnitModule ret = null;
            m_modules.TryGetValue(name, out ret);
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

        /*

        public GameObject modelGo { get; protected set; }

        public SceneUnit(ulong _id, int _unitType, int _modelId)
        {
            unitId = _id;
            unitType = _unitType;
            faceDir = 0.0f;
            pos = Vector3.zero;

            this.LoadModelResource();
        }

        protected void LoadModelResource()
        {
            Object prefab = null;
            if (5 == unitType)
            {
                prefab = Resources.Load("Effect/Missile/GuidedMissile");
            }
            else
            {
                prefab = Resources.Load("Heros/xiaoqiao_blue");
            }

            GameObject go = GameObject.Instantiate(prefab) as GameObject;
            go.transform.SetParent(App.instance.scene.rootSceneObejcts);
            go.SetActive(true);
            modelGo = go;
        }
        */
    }
}


