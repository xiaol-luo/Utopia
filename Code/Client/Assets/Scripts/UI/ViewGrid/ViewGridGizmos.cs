
using System.Collections.Generic;
using UnityEngine;

class ViewGridGizmos : MonoBehaviour
{
    public static ViewGridGizmos GetViewGridGizmosFromScene()
    {
        ViewGridGizmos vgg = GameObject.FindObjectOfType<ViewGridGizmos>();
        if (null == vgg)
        {
            GameObject vggGo = new GameObject("vgg");
            vgg = vggGo.AddComponent<ViewGridGizmos>();
        }
        return vgg;
    }

    static Dictionary<ViewGridNodeType, Color> s_colors = new Dictionary<ViewGridNodeType, Color>()
    {
        {ViewGridNodeType.Ground, new Color(0, 0, 1) },
        {ViewGridNodeType.Wall, new Color(1, 0, 0) },
        {ViewGridNodeType.Grass, new Color(0, 1, 0) },
    };

    public void ClearAll()
    {
        m_allGrids.Clear();
        m_snapshotIdxs.Clear();
    }

    Vector3 m_gridSize = Vector3.one;
    int m_row_num = 0;
    int m_col_num = 0;

    class DrawViewGrid
    {
        public Vector3 center;
        public ViewGridNodeType grid_type;
    }

    List<DrawViewGrid> m_allGrids = new List<DrawViewGrid>();
    List<int> m_snapshotIdxs = new List<int>();

    public void SetAllGrids(NetProto.ViewAllGrids msg)
    {
        m_gridSize = new Vector3(msg.GridSize, 0.2f, msg.GridSize);
        m_row_num = msg.Row;
        m_col_num = msg.Col;
        m_allGrids.Clear();
        foreach (var item in msg.Grids)
        {
            DrawViewGrid dwg = new DrawViewGrid();
            dwg.grid_type = (ViewGridNodeType)item.GridType;
            dwg.center = new Vector3(item.Center.X, 0, item.Center.Y);
            m_allGrids.Add(dwg);
        }
    }

    public void SetSnapshot(NetProto.ViewSnapshot msg)
    {
        m_snapshotIdxs = new List<int>(msg.LightGrids);
    }

    void OnDrawGizmos()
    {
        Color oldColor = Gizmos.color;

        foreach (DrawViewGrid grid in m_allGrids)
        {
            Gizmos.color = s_colors[grid.grid_type];
            Gizmos.DrawWireCube(grid.center, m_gridSize);
        }
        Gizmos.color = new Color(1, 0, 1);
        foreach (int idx in m_snapshotIdxs)
        {
            if (idx >= m_allGrids.Count)
                continue;
            DrawViewGrid grid = m_allGrids[idx];
            Gizmos.DrawCube(grid.center, m_gridSize);
        }
        Gizmos.color = oldColor;
    }
}

