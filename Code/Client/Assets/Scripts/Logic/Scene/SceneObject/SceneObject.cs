
using NetProto;
using UnityEngine;

public class SceneObjcet
{
    public ulong id { get; protected set; }
    public int unitType { get; protected set; }
    public int modelId { get; protected set; }
    public float faceDir {
        get { return m_faceDir; }
        set {
            m_faceDir = value;
            if (null != modelGo)
                modelGo.transform.localRotation = Quaternion.AngleAxis(m_faceDir, Vector3.up);
        }
    }
    float m_faceDir = 0.0f;
    public Vector3 pos
    {
        get { return m_pos; }
        set
        {
            m_pos = value;
            if (null != modelGo)
            {
                modelGo.transform.localPosition = m_pos;
            }
        }
    }

    public void SetPos(NetProto.PBVector3 value)
    {
        pos = new Vector3(value.X, value.Y, value.Z);
    }
    public void SetPos(Vector3 value)
    {
        pos = value;
    }

    public Vector3 m_pos;

    public GameObject modelGo { get; protected set; }

    public SceneObjcet(ulong _id, int _unitType, int _modelId)
    {
        id = _id;
        unitType = _unitType;
        modelId = _modelId  ;
        faceDir = 0.0f;
        pos = Vector3.zero;

        this.LoadModelResource();
    }

    protected void LoadModelResource()
    {
        Object prefab = Resources.Load("Heros/xiaoqiao_blue");
        GameObject go = GameObject.Instantiate(prefab) as GameObject;
        go.transform.SetParent(App.my.scene.rootSceneObejcts);
        go.SetActive(true);
        modelGo = go;
    }
}

