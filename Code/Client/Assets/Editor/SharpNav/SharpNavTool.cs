using System.Collections;
using System.Collections.Generic;
using System.IO;

using UnityEngine;
using UnityEditor;
using UnityEngine.SceneManagement;

using SharpNav;
using SharpNav.Geometry;
using SharpNav.IO.Json;

public class SharpNavTool
{
    #region MenuItem

    [MenuItem("Tools/SharpNav工具/导出SharpNav导航网格(.snb格式)")]
    public static SharpNav.TiledNavMesh ExportSharpNavMesh()
    {
        List<Triangle3> tris = SharpNavTool.FindInputData(UnityNavMeshTool.SceneBuildingRootName);
        if (tris == null || tris.Count == 0)
        {
            Debug.LogError("场景里没有找到能烘培的三角面！");
            return null;
        }

        SharpNav.NavMesh nm = SharpNav.NavMesh.Generate(tris, NavMeshGenerationSettings.Default);
        ExportCurrentSceneSharpNav(nm);
        return nm;
    }

    [MenuItem("Tools/SharpNav工具/生成SharpNav导航网格")]
    static void GenSharpNavMesh()
    {
        TiledNavMesh tiledNavMesh = BakeSharpNave(UnityNavMeshTool.SceneBuildingRootName, NavMeshGenerationSettings.Default);
        if (tiledNavMesh == null)
            return;

        SharpNavDrawer drawer = Camera.main.GetComponent<SharpNavDrawer>();
        if (drawer == null)
            drawer = Camera.main.gameObject.AddComponent<SharpNavDrawer>();

        drawer.SetNavMesh(tiledNavMesh, NavMeshGenerationSettings.Default.VertsPerPoly);
    }
    #endregion

    // ======================================================================

    /// <summary>
    /// 导出当前场景SharpNav数据
    /// </summary>
    /// <param name="mesh"></param>
    public static void ExportCurrentSceneSharpNav (TiledNavMesh mesh)
    {
        string curSceneName = SceneManager.GetActiveScene().name;
        // 保存文件路径
        string fullPath = string.Format("{0}{1}", Application.dataPath, SceneManager.GetActiveScene().path.Substring(6));
        fullPath = fullPath.Substring(0, fullPath.Length - 6) + "/";
        if (!Directory.Exists(fullPath))
            Directory.CreateDirectory(fullPath);
        // 保存文件
        fullPath += curSceneName + ".snb";
        new NavMeshJsonSerializer().Serialize(fullPath, mesh);
        AssetDatabase.Refresh();
    }

    /// <summary>
    /// 加载当前场景SharpNav数据
    /// </summary>
    /// <returns></returns>
    public static TiledNavMesh LoadCurrentSceneSharpNav ()
    {
        // 保存文件路径
        string curSceneName = SceneManager.GetActiveScene().name;
        string fullPath = string.Format("{0}{1}", Application.dataPath, SceneManager.GetActiveScene().path.Substring(6));
        fullPath = fullPath.Substring(0, fullPath.Length - 6) + "/" + curSceneName + ".snb";
        if (File.Exists(fullPath))
        {
            return new NavMeshJsonSerializer().Deserialize(fullPath);
        }

        Debug.LogWarning("没有SharpNav导航网格资源，场景：" + curSceneName);
        return null;
    }

    /// <summary>
    /// 简单烘培SharpNav导航网格
    /// </summary>
    /// <param name="rootName"></param>
    /// <param name="settings"></param>
    /// <returns></returns>
    public static TiledNavMesh BakeSharpNave (string rootName, NavMeshGenerationSettings settings)
    {
        List<Triangle3> tris = SharpNavTool.FindInputData(rootName);

        if (tris == null || tris.Count == 0)
        {
            Debug.LogError("场景里没有找到能烘培的三角面！");
            return null;
        }

        float startTime = Time.realtimeSinceStartup;

        TiledNavMesh navMesh = SharpNav.NavMesh.Generate(tris, settings);

        Debug.LogWarning("烘培sharpnav消耗时间：" + (Time.realtimeSinceStartup - startTime));

        return navMesh;
    }

    /// <summary>
    /// 烘培SharpNav导航网格，可带区域
    /// </summary>
    /// <param name="rootName"></param>
    /// <param name="settings"></param>
    /// <returns></returns>
    public static TiledNavMesh BakeSharpNavWithArea (string rootName, NavMeshGenerationSettings settings)
    {
        List<Triangle3> tris = FindInputData(rootName);
        List<Triangle3> areaTris = FindNotWalkAreaData(rootName);

        if (tris == null || tris.Count == 0)
        {
            Debug.LogError("场景里没有找到能烘培的三角面！");
            return null;
        }

        float startTime = Time.realtimeSinceStartup;
        var triEnumerable = TriangleEnumerable.FromTriangle(tris.ToArray(), 0, tris.Count);
        BBox3 bounds = triEnumerable.GetBoundingBox();

        Heightfield heightfield = new Heightfield(bounds, settings);

        // 这里可以设置区域（暂时默认）
        if (areaTris != null && areaTris.Count > 0)
        {
            Area[] areas = AreaGenerator.From(areaTris.ToArray(), Area.Null).ToArray();
            heightfield.RasterizeTrianglesWithAreas(areaTris.ToArray(), areas);
        }

        heightfield.RasterizeTriangles(tris, Area.Default);


        heightfield.FilterLedgeSpans(settings.VoxelAgentHeight, settings.VoxelMaxClimb);

        heightfield.FilterLowHangingWalkableObstacles(settings.VoxelMaxClimb);

        heightfield.FilterWalkableLowHeightSpans(settings.VoxelAgentHeight);

        CompactHeightfield compactHeightfield = new CompactHeightfield(heightfield, settings);

        compactHeightfield.Erode(settings.VoxelAgentRadius);

        compactHeightfield.BuildDistanceField();

        compactHeightfield.BuildRegions(0, settings.MinRegionSize, settings.MergedRegionSize);

        ContourSet contourSet = compactHeightfield.BuildContourSet(settings);

        PolyMesh polyMesh = new PolyMesh(contourSet, settings);

        PolyMeshDetail polyMeshDetail = new PolyMeshDetail(polyMesh, compactHeightfield, settings);

        NavMeshBuilder buildData = new NavMeshBuilder(polyMesh, polyMeshDetail, new SharpNav.Pathfinding.OffMeshConnection[0], settings);

        TiledNavMesh tiledNavMesh = new TiledNavMesh(buildData);

        Debug.LogWarning("烘培sharpnav消耗时间：" + (Time.realtimeSinceStartup - startTime));

        return tiledNavMesh;
    }
    

    /// <summary>
    /// 查找不可走区域
    /// </summary>
    /// <param name="rootName"></param>
    /// <returns></returns>
    public static List<Triangle3> FindNotWalkAreaData(string rootName, bool useStatic = true)
    {
        GameObject go = GameObject.Find(rootName) as GameObject;
        if (go == null)
        {
            Debug.LogError("当前场景不符合美术规范，没有找到场景对象：" + rootName);
            return null;
        }

        List<Triangle3> tris = new List<Triangle3>();
        List<MeshFilter> areaMeshs = new List<MeshFilter>();

        // 处理场景物和障碍
        foreach (Renderer r in go.transform.GetComponentsInChildren<Renderer>())
        {
            if (useStatic)
            {
                // 判断对象是否需要烘培导航网格的层
                if (!IsNavMeshStatic(r.gameObject))
                {
                    continue;
                }
            }
            else
            {
                Collider col = r.gameObject.GetComponent<Collider>();
                if (col==null)
                {
                    continue;
                }
            }

            MeshFilter mesh = r.gameObject.GetComponent<MeshFilter>();
            if (mesh == null || mesh.sharedMesh == null)
            {
                continue;
            }

            if (!IsNotWalkableArea(r.gameObject))
            {
                continue;
            }

            // 有碰撞的renderer
            areaMeshs.Add(mesh);
        }

        for (int i = 0; i < areaMeshs.Count; ++i)
        {
            Mesh mesh = areaMeshs[i].sharedMesh;
            Debug.Log(string.Format("Object:{2}, triangles:{0}, vertices:{1}", mesh.triangles.Length, mesh.vertices.Length, mesh.name));
            for (int t = 0; t < mesh.triangles.Length; )
            {
                int index = mesh.triangles[t];
                SharpNav.Geometry.Vector3 v3a = new SharpNav.Geometry.Vector3(mesh.vertices[index].x, mesh.vertices[index].y, mesh.vertices[index].z);
                index = mesh.triangles[t + 1];
                SharpNav.Geometry.Vector3 v3b = new SharpNav.Geometry.Vector3(mesh.vertices[index].x, mesh.vertices[index].y, mesh.vertices[index].z);
                index = mesh.triangles[t + 2];
                SharpNav.Geometry.Vector3 v3c = new SharpNav.Geometry.Vector3(mesh.vertices[index].x, mesh.vertices[index].y, mesh.vertices[index].z);
                Triangle3 t3 = new Triangle3(v3a, v3b, v3c);
                t += 3;
                tris.Add(t3);
            }
        }

        return tris;
    }

    /// <summary>
    /// 获取需要烘培的三角面
    /// </summary>
    /// <param name="rootName"></param>
    /// <param name="useStatic">true:查找静态对象的, false:查找碰撞体对象的</param>
    public static List<Triangle3> FindInputData(string rootName, bool useStatic = true)
    {
        // 获取需要生成导航网格的场景对象
        GameObject go = GameObject.Find(rootName) as GameObject;
        if (go == null)
        {
            Debug.LogError("当前场景不符合美术规范，没有找到场景对象：" + rootName);
            return null;
        }

        float startTime = Time.realtimeSinceStartup;

        List<Triangle3> tris = new List<Triangle3>();
        // 导航网格的生成是依赖Renderer，工程里需要有碰撞和Renderer才生成导航网格
        // 项目需求：如果renderer没有collider的对象，不烘焙导航网格
        List<MeshFilter> inputMeshs = new List<MeshFilter>();

        // 处理Terrain
        foreach (Terrain t in go.transform.GetComponentsInChildren<Terrain>())
        {
            TerrainCollider col = t.GetComponent<TerrainCollider>();
            if (col == null)
            {
                // 没地形碰撞的不处理
                continue;
            }
            Debug.LogError("场景含有Terrain组件，SharpNav无法处理，地形名称：" + t.gameObject.name);
        }

        // 处理场景物和障碍
        foreach (Renderer r in go.transform.GetComponentsInChildren<Renderer>())
        {
            if (useStatic)
            {
                // 判断对象是否需要烘培导航网格的层
                if (!IsNavMeshStatic(r.gameObject))
                {
                    continue;
                }
            }
            else
            {
                Collider col = r.gameObject.GetComponent<Collider>();
                if (col==null)
                {
                    continue;
                }
            }

            MeshFilter mesh = r.gameObject.GetComponent<MeshFilter>();
            if (mesh == null || mesh.sharedMesh == null)
            {
                continue;
            }
            // 有碰撞的renderer
            inputMeshs.Add(mesh);
        }

        // 生成Unity的NavMesh
        for (int i = 0; i < inputMeshs.Count; ++i)
        {
            Mesh mesh = inputMeshs[i].sharedMesh;
            Transform transfrom = inputMeshs[i].transform;
            Debug.Log(string.Format("Object:{2}, triangles:{0}, vertices:{1}, subMesh:{3}", mesh.triangles.Length, mesh.vertices.Length, mesh.name, mesh.subMeshCount));
            for (int subIndex = 0; subIndex < mesh.subMeshCount; ++subIndex)
            {
                int[] triIndexs = mesh.GetTriangles(subIndex);
                for (int t = 0; t < triIndexs.Length; t += 3)
                {
                    int index = triIndexs[t];
                    UnityEngine.Vector3 v3 = transfrom.TransformPoint(mesh.vertices[index]);
                    SharpNav.Geometry.Vector3 v3a = new SharpNav.Geometry.Vector3(v3.x, v3.y, v3.z);
                    index = triIndexs[t + 1];
                    v3 = transfrom.TransformPoint(mesh.vertices[index]);
                    SharpNav.Geometry.Vector3 v3b = new SharpNav.Geometry.Vector3(v3.x, v3.y, v3.z);
                    index = triIndexs[t + 2];
                    v3 = transfrom.TransformPoint(mesh.vertices[index]);
                    SharpNav.Geometry.Vector3 v3c = new SharpNav.Geometry.Vector3(v3.x, v3.y, v3.z);
                    Triangle3 t3 = new Triangle3(v3a, v3b, v3c);
                    tris.Add(t3);
                }
            }
        }

        Debug.LogWarning("收集mesh消耗时间："+(Time.realtimeSinceStartup - startTime));

        return tris;
    }

    public static bool IsNavMeshStatic(GameObject go)
    {
        if ((GameObjectUtility.GetStaticEditorFlags(go) & StaticEditorFlags.NavigationStatic) == StaticEditorFlags.NavigationStatic)
            return true;

        return false;
    }

    public static bool IsWalkableArea(GameObject go)
    {
        int areaType = GameObjectUtility.GetNavMeshArea(go);
        if (areaType == GameObjectUtility.GetNavMeshAreaFromName("Walkable"))
            return true;

        return false;
    }

    public static bool IsNotWalkableArea(GameObject go)
    {
        int areaType = GameObjectUtility.GetNavMeshArea(go);
        if (areaType == GameObjectUtility.GetNavMeshAreaFromName("Not Walkable"))
            return true;

        return false;
    }

}
