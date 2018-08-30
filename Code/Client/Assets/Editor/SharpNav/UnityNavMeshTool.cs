using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.AI;
using UnityEngine;
using UnityEngine.AI;
using System.IO;
using System.Text;
using UnityEngine.SceneManagement;

public class UnityNavMeshTool
{
    // NavMeshLayer Values
    const int NavMeshLayer = 30;
    const string NavMeshLayerName = "NavMesh";
    public const string SceneBuildingRootName = "Building";

    #region Menu Tools

    [MenuItem("Tools/Unity导航网格工具/烘培Unity导航网格")]
    static void BuildMapSceneUnityNavMesh()
    {
        BakeUnityNavMesh(SceneBuildingRootName);
    }

    [MenuItem("Tools/Unity导航网格工具/创建Unity导航网格对象")]
    static void CreateCurrentUnityNavMesh()
    {
        SimpleGenUnityNavMeshObj(true);
    }

    [MenuItem("Tools/Unity导航网格工具/导出Unity导航网格(.json格式)")]
    static void ExportUnityNavMeshJson()
    {
        GenUnityNavMesh(0);
    }

    [MenuItem("Tools/Unity导航网格工具/导出Unity导航网格(.obj格式)")]
    static void ExportUnityNavMeshObj()
    {
        GenUnityNavMesh(1);
    }

    #endregion

    /// <summary>
    /// 生成Unity的NavMesh
    /// </summary>
    /// <param name="rootName"></param>
    /// <param name="withLayer"></param>
    public static void BakeUnityNavMesh(string rootName, bool withLayer=false)
    {
        // 获取需要生成导航网格的场景对象
        GameObject go = GameObject.Find(rootName) as GameObject;
        if (go == null)
        {
            Debug.LogError("当前场景不符合美术规范，没有找到场景对象：" + SceneBuildingRootName);
            return;
        }

        // 导航网格的生成是依赖Renderer，工程里需要有碰撞和Renderer才生成导航网格
        // 项目需求：如果renderer没有collider的对象，不烘焙导航网格

        int bakeRendererCount = 0;
        // 处理Terrain
        foreach (Terrain t in go.transform.GetComponentsInChildren<Terrain>())
        {
            TerrainCollider col = t.GetComponent<TerrainCollider>();
            if (col==null)
            {

                continue;
            }
            Debug.LogError("场景含有Terrain组件，地形名称：" + t.gameObject.name);
            SetOnlyNavMeshStatic(t.gameObject);
            bakeRendererCount += 1;
        }
        
        // 处理场景物和障碍
        List<Renderer> renderObject = new List<Renderer>();
        List<Renderer> hideObject = new List<Renderer>();
        foreach (Renderer r in go.transform.GetComponentsInChildren<Renderer>())
        {
            Collider col = r.gameObject.GetComponent<Collider>();
            if (col == null)
            {
                // 没碰撞的不烘培导航网格，并把renderer隐藏
                if (r.enabled)
                {
                    renderObject.Add(r);
                    r.enabled = false;
                }
            }
            else
            {
                // 判断对象是否需要烘培导航网格的层
                if (withLayer && !IsNavMeshLayer(r.gameObject))
                {
                    if (r.enabled)
                    {
                        renderObject.Add(r);
                        r.enabled = false;
                    }
                    continue;
                }

                // 有碰撞的renderer

                //如果有碰撞的renderer隐藏了，要临时激活
                if (!r.enabled)
                {
                    hideObject.Add(r);
                    r.enabled = true;
                }

                // 设置static
                SetOnlyNavMeshStatic(r.gameObject);
                bakeRendererCount += 1;
            }
        }

        // 检查日志输出
        if (bakeRendererCount == 0)
            Debug.LogWarning("没有找到能烘培Unity导航网格的对象！");

        // 生成Unity的NavMesh
        UnityEditor.AI.NavMeshBuilder.BuildNavMesh();

        // 把renderer激活
        foreach (Renderer r in renderObject)
            r.enabled = true;

        // 把renderer隐藏
        foreach (Renderer r in hideObject)
            r.enabled = false;
    }

    /// <summary>
    /// 获取Unity的导航网格对象数据
    /// </summary>
    /// <param name="style">0 json格式, 1 obj格式</param>
    /// <returns></returns>
    public static void GenUnityNavMesh(int style)
    {
        List<Vector3> repos = new List<Vector3>();// 顶点
        Dictionary<int, int> indexMap = new Dictionary<int, int>();// 每个顶点的索引表
        List<int[]> polys = new List<int[]>();// 多边形顶点索引列表
        bool ok = CalUnityNavMeshData(out repos, out indexMap, out polys);
        if (!ok)
            return;

        // 保存文件路径
        string curSceneName = SceneManager.GetActiveScene().name;
        string fullPath = string.Format("{0}{1}", Application.dataPath, SceneManager.GetActiveScene().path.Substring(6));
        fullPath = fullPath.Substring(0, fullPath.Length - 6) + "/";
        if (!Directory.Exists(fullPath))
            Directory.CreateDirectory(fullPath);

        // 生成文件
        System.Text.StringBuilder strBuilder = new StringBuilder();
        // Json
        if (style == 0)
        {
            // 顶点
            strBuilder.AppendLine("{\"v\":[");
            for (int i = 0; i < repos.Count; i++)
            {
                if (i > 0)
                    strBuilder.AppendLine(",");

                strBuilder.AppendFormat("[{0},{1},{2}]", repos[i].x, repos[i].y, repos[i].z);
            }
            strBuilder.AppendLine();

            // 索引
            strBuilder.AppendLine("],\"p\":[");
            for (int i = 0; i < polys.Count; i++)
            {
                string outs = indexMap[polys[i][0]].ToString();
                for (int j = 1; j < polys[i].Length; j++)
                {
                    outs += "," + indexMap[polys[i][j]];
                }

                if (i > 0)
                    strBuilder.AppendLine(",");

                strBuilder.AppendFormat("[{0}]", outs);
            }
            strBuilder.AppendLine();
            strBuilder.Append("]}");

            // 保存文件
            fullPath += curSceneName + ".json";
            File.WriteAllText(fullPath, strBuilder.ToString());
            AssetDatabase.Refresh();

            Debug.Log(string.Format("生成Unity导航网格.json文件：{0}", fullPath));
        }
        else if (style == 1)// Object
        {
            // 顶点
            for (int i = 0; i < repos.Count; i++)
            {
                //unity 对obj 做了 x轴 取反
                strBuilder.AppendLine(string.Format("v {0} {1} {2}", (repos[i].x * -1.0f), repos[i].y, repos[i].z));
            }

            // 换行
            strBuilder.AppendLine("g default");

            // 多边形的顶点索引
            for (int i = 0; i < polys.Count; i++)
            {
                strBuilder.Append("f");
                // 逆向
                for (int j = polys[i].Length - 1; j >= 0; j--)
                {
                    strBuilder.Append(" " + (indexMap[polys[i][j]] + 1));
                }
                strBuilder.AppendLine();
            }

            // 保存文件
            fullPath += curSceneName + ".obj";
            File.WriteAllText(fullPath, strBuilder.ToString());
            AssetDatabase.Refresh();

            Debug.Log(string.Format("生成Unity导航网格.obj文件：{0}", fullPath));
        }
    }

    public static void SimpleGenUnityNavMeshObj(bool showTestMesh=false)
    {

        string curSceneName = SceneManager.GetActiveScene().name;
        UnityEngine.AI.NavMeshTriangulation data = UnityEngine.AI.NavMesh.CalculateTriangulation();
        if (data.vertices==null || data.vertices.Length==0)
        {
            Debug.LogWarning(string.Format("场景：{0}，没有烘培Unity的导航网格，不能生成导航网格的.obj文件!", curSceneName));
            return;
        }

        // 测试NavMesh，直接生成模型mesh展示
        // 实际NavMesh的顶点列表和顶点索引列表是一致的
        if (showTestMesh)
        {
            var obj = GameObject.CreatePrimitive(PrimitiveType.Cube);
            obj.name = curSceneName;
            var mf = obj.GetComponent<MeshFilter>();
            Mesh m = new Mesh();
            m.name = curSceneName;
            m.vertices = data.vertices;
            m.triangles = data.indices;
            mf.mesh = m;
        }

        Debug.Log("ExportNavMesh Start");
        
        // 保存文件路径
        string fullPath = string.Format("{0}{1}", Application.dataPath, SceneManager.GetActiveScene().path.Substring(6));
        fullPath = fullPath.Substring(0, fullPath.Length - 6) + "/";
        if (!Directory.Exists(fullPath))
            Directory.CreateDirectory(fullPath);
        fullPath += curSceneName + ".obj";
        StreamWriter tmpStreamWriter = new StreamWriter(fullPath);

        //顶点  
        for (int i = 0; i < data.vertices.Length; i++)
        {
            tmpStreamWriter.WriteLine("v  " + data.vertices[i].x + " " + data.vertices[i].y + " " + data.vertices[i].z);
        }

        tmpStreamWriter.WriteLine("g default");

        //顶点索引  
        for (int i = 0; i < data.indices.Length; )
        {
            tmpStreamWriter.WriteLine("f " + (data.indices[i] + 1) + " " + (data.indices[i + 1] + 1) + " " + (data.indices[i + 2] + 1));
            i = i + 3;
        }

        tmpStreamWriter.Flush();
        tmpStreamWriter.Close();

        Debug.Log("ExportUnityNavMesh Success:" + fullPath);  
    }

    /// <summary>
    /// 计算导航网格信息
    /// </summary>
    /// <param name="repos"></param>
    /// <param name="indexMap"></param>
    /// <param name="polys"></param>
    public static bool CalUnityNavMeshData(out List<Vector3> repos, out Dictionary<int, int> indexMap, out List<int[]> polys)
    {
        repos = new List<Vector3>();// 顶点
        indexMap = new Dictionary<int, int>();// 每个顶点的索引表
        polys = new List<int[]>();// 多边形顶点索引列表

        string curSceneName = SceneManager.GetActiveScene().name;
        UnityEngine.AI.NavMeshTriangulation navData = UnityEngine.AI.NavMesh.CalculateTriangulation();
        if (navData.vertices == null || navData.vertices.Length == 0)
        {
            Debug.LogWarning(string.Format("场景：{0}，没有烘培Unity的导航网格，无法计算导航网格信息!", curSceneName));
            return false;
        }

        // 计算顶点和顶点索引表
        for (int i = 0; i < navData.vertices.Length; i++)
        {
            int ito = -1;
            for (int j = 0; j < repos.Count; j++)
            {
                if (Vector3.Distance(navData.vertices[i], repos[j]) < 0.01f)
                {
                    ito = j;
                    break;
                }
            }
            if (ito < 0)
            {
                indexMap[i] = repos.Count;
                repos.Add(navData.vertices[i]);
            }
            else
            {
                indexMap[i] = ito;
            }
        }

        //关系是 index 公用的三角形表示他们共同组成多边形
        //多边形之间的连接用顶点位置识别
        List<int> polyIndex = new List<int>();// 每个多边形的顶点索引
        for (int i = 0; i < navData.indices.Length / 3; i++)
        {
            int i0 = navData.indices[i * 3 + 0];
            int i1 = navData.indices[i * 3 + 1];
            int i2 = navData.indices[i * 3 + 2];

            if (polyIndex.Contains(i0) || polyIndex.Contains(i1) || polyIndex.Contains(i2))
            {
                if (!polyIndex.Contains(i0))
                    polyIndex.Add(i0);
                if (!polyIndex.Contains(i1))
                    polyIndex.Add(i1);
                if (!polyIndex.Contains(i2))
                    polyIndex.Add(i2);
            }
            else
            {
                if (polyIndex.Count > 0)
                {
                    polys.Add(polyIndex.ToArray());
                }
                polyIndex.Clear();
                polyIndex.Add(i0);
                polyIndex.Add(i1);
                polyIndex.Add(i2);
            }
        }
        if (polyIndex.Count > 0)
        {
            polys.Add(polyIndex.ToArray());
        }

        return true;
    }

    // =====================================================

    public static bool IsNavMeshLayer(GameObject go)
    {
        if (go.layer == LayerMask.NameToLayer(NavMeshLayerName))
            return true;

        return false;
    }

    public static void SetNavMeshStatic(GameObject go)
    {
        GameObjectUtility.SetStaticEditorFlags(go, GameObjectUtility.GetStaticEditorFlags(go) | StaticEditorFlags.NavigationStatic);
    }

    public static void SetOnlyNavMeshStatic(GameObject go)
    {
        GameObjectUtility.SetStaticEditorFlags(go, StaticEditorFlags.NavigationStatic);
    }

    public static void UnsetNavMeshStatic(GameObject go)
    {
        GameObjectUtility.SetStaticEditorFlags(go, GameObjectUtility.GetStaticEditorFlags(go) & ~StaticEditorFlags.NavigationStatic);
    }

}
