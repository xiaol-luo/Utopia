
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UnityEngine;

[ExecuteInEditMode]
public class ViewGridEditor : MonoBehaviour
{
    float m_oldGridSize = 0;
    float m_oldRowCount= 0;
    float m_oldColCount = 0;
    // [SerializeField]
    float m_gridSize = 1.0f;
    // [SerializeField]
    int m_rowCount = 100;
    // [SerializeField]
    int m_colCount = 100;

    List<List<ViewGridNodeType>> m_grid = new List<List<ViewGridNodeType>>();
    bool CheckGridSize(bool onlyCheck)
    {
        if (m_oldColCount == m_colCount && m_rowCount == m_oldRowCount)
            return false;
        else
        {
            if (onlyCheck)
                return true;
        }

        m_oldRowCount = m_rowCount;
        m_oldColCount = m_colCount;

        if (m_rowCount < 0)
            m_rowCount = 0;
        if (m_colCount < 0)
            m_colCount = 0;

        if (m_grid.Count > m_rowCount)
        {
            m_grid = m_grid.GetRange(0, m_rowCount);
        }
        else
        {
            for (int i = m_grid.Count; i < m_rowCount; ++i)
                m_grid.Add(new List<ViewGridNodeType>());
        }
        for (int i = 0; i < m_grid.Count; ++i)
        {
            if (m_grid[i].Count > m_colCount)
            {
                m_grid[i] = m_grid[i].GetRange(0, m_colCount);
            }
            else
            {
                for (int j = m_grid[i].Count; j < m_colCount; ++j)
                    m_grid[i].Add(ViewGridNodeType.Ground);
            }
        }

        return true;
    }

    private void Start()
    {
        Load("eos_navmesh.view");
        Invoke("HeartBeat", 0.1f);
    }

    void HeartBeat()
    {
        Invoke("HeartBeat", 0.1f);
        this.CheckChange();
    }

    void OnNodeTypeChange(int row, int col, ViewGridNodeType nodeType)
    {
        m_grid[row][col] = nodeType;
        this.Save("eos_navmesh.view");
    }

    public void Load(string filePath)
    {
        string [] lines = File.ReadAllLines(filePath);
        if (null == lines || lines.Length <= 0)
            return;

        if (lines.Length >= 1)
        {
            string[] strs = lines[0].Split(' ');
            if (strs.Length < 3)
                return;

            m_gridSize = float.Parse(strs[0]);
            m_rowCount = int.Parse(strs[1]);
            m_colCount = int.Parse(strs[2]);
        }

        m_oldRowCount = m_rowCount - 1;
        this.CheckGridSize(false);
        if (lines.Length >= 2)
        {
            string[] strs = lines[1].Split(' ');
            int idx = 0;
            for (int row = 0; row < m_grid.Count; ++ row)
            {
                for (int col = 0; col < m_grid[row].Count; ++ col)
                {
                    m_grid[row][col] = ViewGridNodeType.Ground;
                    if (idx < strs.Length)
                    {
                        m_grid[row][col] = (ViewGridNodeType)int.Parse(strs[idx]);
                        ++idx;
                    }

                    /*
                    if (row >= 57 && row <= 82 && col >= 42 && col <= 67)
                        m_grid[row][col] = ViewGridNodeType.Grass;
                    if (row >= 29 && row <= 30 && col >= 30 && col <= 69)
                        m_grid[row][col] = ViewGridNodeType.Wall;
                    */
                }
            }
        }
        m_oldGridSize = m_gridSize - 1;
        this.CheckChange();
        this.Save(filePath);
    }
    public void Save(string filePath)
    {
        StringBuilder sb = new StringBuilder();
        sb.AppendFormat("{0} {1} {2}\n", m_gridSize, m_rowCount, m_colCount);

        int gridCount = 0;
        foreach (var nodes in m_grid)
        {
            foreach (ViewGridNodeType val in nodes)
            {
                ++gridCount;
                sb.AppendFormat("{0} ", (int)val);
            }
        }
        if (gridCount > 0)
        {
            sb.Remove(sb.Length - 1, 1);
        }
        File.WriteAllText(filePath, sb.ToString());
    }

    private void Reset()
    {
        
    }

    private void OnValidate()
    {
        
    }

    List<GameObject> m_cachedGos = new List<GameObject>();
    private void CheckChange()
    {
        if (m_gridSize == m_oldGridSize && !this.CheckGridSize(false))
            return;

        m_oldGridSize = m_gridSize;

        GameObject DestroyingGos = GameObject.Find("DestroyingGos");
        if (DestroyingGos == null)
            DestroyingGos = new GameObject("DestroyingGos");
        for (int i = this.transform.childCount - 1; i >= 0; --i)
        {
            GameObject go = this.transform.GetChild(i).gameObject;
            go.transform.SetParent(DestroyingGos.transform);
            go.SetActive(false);
            // GameObject.Destroy(go);
            m_cachedGos.Add(go);
        }

        float halfGridSize = m_gridSize / 2;
        for (int row = 0; row < m_grid.Count; ++row)
        {
            float x = halfGridSize + m_gridSize * row;
            for (int col = 0; col < m_grid[row].Count; ++col)
            {
                float z = halfGridSize + m_gridSize * col;
                GameObject cube = null;
                if (m_cachedGos.Count > 0)
                {
                    cube = m_cachedGos[0];
                    m_cachedGos.RemoveAt(0);
                }
                else
                {
                    cube = new GameObject();
                }
                cube.name = string.Format("{0}-{1}", row, col);
                cube.SetActive(true);
                cube.transform.SetParent(this.transform);
                cube.transform.localPosition = new Vector3(x, 0, z);
                cube.transform.localScale = new Vector3(m_gridSize, 1, m_gridSize);

                ViewGridNode gridNode = cube.GetComponent<ViewGridNode>();
                if (null == gridNode)
                    gridNode = cube.AddComponent<ViewGridNode>();
                gridNode.row = row;
                gridNode.col = col;
                gridNode.size = m_gridSize;
                gridNode.onNodeTypeChange = this.OnNodeTypeChange;
                ViewGridNodeType nodeType = m_grid[row][col];
                gridNode.SetColor(nodeType, false);
            }
        }
    }
}
