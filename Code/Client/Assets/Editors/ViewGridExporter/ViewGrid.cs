using System.Collections.Generic;
using UnityEngine;

public enum ViewGridNodeType
{
    Ground = 0,
    Wall = 1,
    Grass = 2
}

[ExecuteInEditMode]
public class ViewGridNode : MonoBehaviour
{
    static Dictionary<ViewGridNodeType, Color> s_colors = new Dictionary<ViewGridNodeType, Color>()
    {
        {ViewGridNodeType.Ground, new Color(0, 0, 1) },
        {ViewGridNodeType.Wall, new Color(1, 0, 0) },
        {ViewGridNodeType.Grass, new Color(0, 1, 0) },
    };

    [SerializeField]
    public int row;
    [SerializeField]
    public int col;
    [SerializeField]
    public ViewGridNodeType m_nodeType = ViewGridNodeType.Ground;
    ViewGridNodeType m_oldNodeType = ViewGridNodeType.Ground;
    public System.Action<int, int, ViewGridNodeType> onNodeTypeChange;
    [SerializeField]
    public float size;

    public void SetColor(ViewGridNodeType value, bool triggerCb)
    {
        m_nodeType = value;
        m_oldNodeType = m_nodeType;

        Renderer comp = this.GetComponent<Renderer>();
        if (null != comp)
        {
            // comp.material.color = s_colors[m_nodeType];
        }

        if (triggerCb && null != onNodeTypeChange)
            onNodeTypeChange(row, col, m_nodeType);
    }

    private void Start()
    {

    }

#if UNITY_EDITOR

    private void Reset()
    {
        this.CheckChange();
    }

    private void OnValidate()
    {
        this.CheckChange();
    }
#endif

    private void CheckChange()
    {
        if (m_nodeType != m_oldNodeType)
        {
            this.SetColor(m_nodeType, true);
        }
    }

    void OnDrawGizmos()
    {
        // Gizmos.DrawIcon(transform.position, "green_ball.png", true);
        Gizmos.color = s_colors[m_nodeType];
        Gizmos.DrawWireCube(transform.position, new Vector3(size, 1, size));
    }
}