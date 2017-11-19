using System.Collections.Generic;
using UnityEngine;

public class GizmosDrawWireMesh : MonoBehaviour
{
    public Color color = new Color(0, 0, 1);

    MeshFilter m_meshFilter = null;
    private void Start()
    {
        m_meshFilter = this.GetComponent<MeshFilter>();
    }

    void OnDrawGizmos()
    {
        Color oldColor = Gizmos.color;
        Matrix4x4 oldMatri = Gizmos.matrix;
        if (null != m_meshFilter && null != m_meshFilter.mesh)
        {
            Gizmos.color = color;
            Gizmos.matrix = Matrix4x4.Scale(this.transform.lossyScale);
            Gizmos.DrawWireMesh(m_meshFilter.mesh, this.transform.position, this.transform.rotation);
        }
        Gizmos.color = oldColor;

        Gizmos.matrix = oldMatri;
    }
}