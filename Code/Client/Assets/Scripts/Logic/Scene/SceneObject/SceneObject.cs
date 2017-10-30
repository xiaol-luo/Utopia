
using NetProto;
using UnityEngine;

public class SceneObjcet
{
    public long id { get; protected set; }
    public NetProto.ESceneObject objectType { get; protected set; }
    public int modelId { get; protected set; }
    public float faceDir {
        get { return m_faceDir; }
        set { m_faceDir = value; } }
    float m_faceDir = 0.0f;
    public Vector3 position
    {
        get { return m_position; }
        set
        {
            m_position = value;
            if (null != modelGo)
            {
                modelGo.transform.localPosition = m_position;
            }
        }
    }
    public Vector3 m_position;

    public GameObject modelGo { get; protected set; }

    public SceneObjcet(long _id, NetProto.ESceneObject _objType, int _modelId)
    {
        id = _id;
        objectType = _objType;
        modelId = _modelId  ;
        faceDir = 0.0f;
        position = Vector3.zero;

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

