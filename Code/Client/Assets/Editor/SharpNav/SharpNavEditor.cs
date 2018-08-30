using System.Collections;
using System.Collections.Generic;

using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;
using SharpNav;

public class SharpNavEditor : EditorWindow
{

    private enum DisplayMode
    {
        None,
        Heightfield,
        CompactHeightfield,
        DistanceField,
        Regions,
        Contours,
        PolyMesh,
        PolyMeshDetail,
        NavMesh,
        Pathfinding,
    }

    private static NavMeshGenerationSettings m_buildSetting = NavMeshGenerationSettings.Default;
    public static NavMeshGenerationSettings Setting
    {
        get { return m_buildSetting; }
    }

    TiledNavMesh m_tiledNavMesh;
    SharpNavDrawer m_navDrawer;
    string m_sceneName;

    private Vector2 m_ScrollPos = Vector2.zero;
    private bool m_step1 = true;
    private bool m_step2 = true;
    private bool m_step3 = true;
    private bool m_step4 = true;

    [MenuItem("Tools/SharpNav工具/SharpNav编辑工具", false, 100)]
    static void SetupWindow()
    {
        SharpNavEditor editor = GetWindow<SharpNavEditor>("SharpNav");
        editor.autoRepaintOnSceneChange = true;
        editor.minSize = new Vector2(300, 360);
    }

    public void OnEnable()
    {
        m_sceneName = SceneManager.GetActiveScene().name;
        m_tiledNavMesh = SharpNavTool.LoadCurrentSceneSharpNav();

        // 初始化NavDrawer
        InitNavDrawer();

        Repaint();
    }

    public void OnDisable()
    {
        // 销毁NavDrawer
        if (m_navDrawer!=null)
        {
            GameObject.DestroyImmediate(m_navDrawer);
            m_navDrawer = null;
        }
    }

    public void OnHierarchyChange()
    {
        if (m_sceneName!=SceneManager.GetActiveScene().name)
        {
            m_sceneName = SceneManager.GetActiveScene().name;
            // 先销毁旧的
            if (m_navDrawer != null)
            {
                GameObject.DestroyImmediate(m_navDrawer);
                m_navDrawer = null;
            }

            m_tiledNavMesh = SharpNavTool.LoadCurrentSceneSharpNav();
            InitNavDrawer();
        }
    }

    public void OnGUI()
    {
        using (var sv = new EditorGUILayout.ScrollViewScope(m_ScrollPos))
        {
            m_ScrollPos = sv.scrollPosition;
            BakeSetting();
        }
    }

    void InitNavDrawer ()
    {
        if (Camera.main != null)
        {
            m_navDrawer = Camera.main.GetComponent<SharpNavDrawer>();
            if (m_navDrawer == null)
            {
                m_navDrawer = Camera.main.gameObject.AddComponent<SharpNavDrawer>();
            }
            if (m_navDrawer != null)
                m_navDrawer.SetNavMesh(m_tiledNavMesh, m_buildSetting.VertsPerPoly);
        }
    }

    void BakeSetting()
    {
        // 使用说明和步骤
        EditorGUILayout.Space();
        EditorGUILayout.LabelField(new GUIContent(" 使用说明和步骤"), EditorStyles.boldLabel, new GUILayoutOption[0]);
        EditorGUILayout.HelpBox(
            "1. 设置场景导航网格烘培美术规范.\n" +
            "2. 设置场景导航网格烘培参数，并应用配置.\n" +
            "3. 烘培场景导航网格.\n" +
            "4. 导出导航网格数据(根据需求导出对应格式).", MessageType.Info);

        // Setp 1
        EditorGUILayout.Space();
        m_step1 = EditorGUILayout.Toggle(new GUIContent("Setp 1 : Check Art Scene"), m_step1, EditorStyles.foldout, new GUILayoutOption[0]);
        if (m_step1)
        {
            EditorGUILayout.Space();
            using (new EditorGUILayout.HorizontalScope())
            {
                if (GUILayout.Button("Check Art Scene"))
                {
                    ShowNotification(new GUIContent("未实现！"));
                }
                EditorGUILayout.Space();
            }
        }

        // Agent
        EditorGUILayout.Space();
        EditorGUILayout.Space();
        m_step2 = EditorGUILayout.Toggle(new GUIContent("Setp 2 : Bake Setting"), m_step2, EditorStyles.foldout, new GUILayoutOption[0]);
        if (m_step2)
        {
            EditorGUILayout.LabelField(new GUIContent("Baked Agent Size"), EditorStyles.boldLabel, new GUILayoutOption[0]);

            using (new EditorGUILayout.VerticalScope())
            {
                float num = EditorGUILayout.FloatField("Agent Radius", m_buildSetting.AgentRadius, new GUILayoutOption[0]);
                if (num >= 0.001f && !Mathf.Approximately(num - m_buildSetting.AgentRadius, 0f))
                {
                    m_buildSetting.AgentRadius = num;
                    m_buildSetting.CellSize = 2f * m_buildSetting.AgentRadius / 6f;
                }
                if (m_buildSetting.AgentRadius < 0.05f)
                {
                    EditorGUILayout.HelpBox("The agent radius you've set is really small, this can slow down the build.\nIf you intended to allow the agent to move close to the borders and walls, please adjust voxel size in advaced settings to ensure correct bake.", MessageType.Warning);
                }
                float num2 = EditorGUILayout.FloatField("Agent Height", m_buildSetting.AgentHeight, new GUILayoutOption[0]);
                if (num2 >= 0.001f && !Mathf.Approximately(num2 - m_buildSetting.AgentHeight, 0f))
                {
                    m_buildSetting.AgentHeight = num2;
                }
                float num3 = EditorGUILayout.FloatField("AgentClimb", m_buildSetting.MaxClimb, new GUILayoutOption[0]);
                if (num3 >= 0f && !Mathf.Approximately(m_buildSetting.MaxClimb - num3, 0f))
                {
                    m_buildSetting.MaxClimb = num3;
                }
                if (m_buildSetting.MaxClimb > m_buildSetting.AgentHeight)
                {
                    EditorGUILayout.HelpBox("Step height should be less than agent height.\nClamping step height to " + m_buildSetting.AgentHeight + " internally when baking.", MessageType.Warning);
                }
                
            }

            // Rasterization
            EditorGUILayout.Space();
            EditorGUILayout.LabelField(new GUIContent("Rasterization"), EditorStyles.boldLabel, new GUILayoutOption[0]);

            using (new EditorGUILayout.VerticalScope())
            {
                // Cell Size
                float tempCellSize = EditorGUILayout.FloatField("CellSize", m_buildSetting.CellSize, new GUILayoutOption[0]);
                if (tempCellSize > 0f && !Mathf.Approximately(tempCellSize - m_buildSetting.CellSize, 0f))
                {
                    m_buildSetting.CellSize = Mathf.Max(0.01f, tempCellSize);
                }
                if (tempCellSize < 0.01f)
                {
                    EditorGUILayout.HelpBox("The voxel size should be larger than 0.01.", MessageType.Warning);
                }
                float tempRadius = (m_buildSetting.CellSize <= 0f) ? 0f : (m_buildSetting.AgentRadius / m_buildSetting.CellSize);
                EditorGUILayout.LabelField(" ", tempRadius.ToString("0.00") + " voxels per agent radius", EditorStyles.miniLabel, new GUILayoutOption[0]);
                float hCellSize = m_buildSetting.CellSize * 0.5f;
                if ((int)Mathf.Floor(m_buildSetting.AgentHeight / hCellSize) > 250)
                {
                    EditorGUILayout.HelpBox("The number of voxels per agent height is too high. This will reduce the accuracy of the navmesh. Consider using voxel size of at least " + (m_buildSetting.AgentHeight / 250f / 0.5f).ToString("0.000") + ".", MessageType.Warning);
                }
                if (tempRadius < 1f)
                {
                    EditorGUILayout.HelpBox("The number of voxels per agent radius is too small. The agent may not avoid walls and ledges properly. Consider using voxel size of at least " + (m_buildSetting.AgentRadius / 2f).ToString("0.000") + " (2 voxels per agent radius).", MessageType.Warning);
                }
                else if (tempRadius > 8f)
                {
                    EditorGUILayout.HelpBox("The number of voxels per agent radius is too high. It can cause excessive build times. Consider using voxel size closer to " + (m_buildSetting.AgentRadius / 8f).ToString("0.000") + " (8 voxels per radius).", MessageType.Warning);
                }

                // Cell Height
                float tempCellHeight = EditorGUILayout.FloatField("CellHeight", m_buildSetting.CellHeight, new GUILayoutOption[0]);
                if (tempCellHeight > 0f && !Mathf.Approximately(tempCellHeight - m_buildSetting.CellHeight, 0f))
                {
                    m_buildSetting.CellHeight = Mathf.Max(0.01f, tempCellHeight);
                }
                if (tempCellHeight < 0.01f)
                {
                    EditorGUILayout.HelpBox("The voxel height should be larger than 0.01.", MessageType.Warning);
                }
                // 单元格高度不能大于爬坡高度
                float climbVal = m_buildSetting.MaxClimb;
                float cellVal = m_buildSetting.CellHeight;
                if (cellVal > climbVal)
                {
                    EditorGUILayout.HelpBox(string.Concat(new string[]
				    {
					    "Step Height conflicts with Max Cell Height. This makes some cells unwalkable.\nConsider decreasing Max Cell Height to < ",
					    climbVal.ToString("0.0"),
					    ".\nOr, increase Step Height to > ",
					    cellVal.ToString("0.00"),
					    "."
				    }), MessageType.Warning);
                }
            }

            // Region
            EditorGUILayout.Space();
            EditorGUILayout.LabelField(new GUIContent("Region"), EditorStyles.boldLabel, new GUILayoutOption[0]);
            using (new EditorGUILayout.VerticalScope())
            {
                // MinRegionArea
                EditorGUILayout.Space();
                int tmpMinRegionArea = EditorGUILayout.IntField("MinRegionArea", m_buildSetting.MinRegionSize, new GUILayoutOption[0]);
                if (tmpMinRegionArea >= 0f && tmpMinRegionArea != m_buildSetting.MinRegionSize)
                {
                    m_buildSetting.MinRegionSize = tmpMinRegionArea;
                }

                // MergedRegionSize
                EditorGUILayout.Space();
                int tmpMergeRegionArea = EditorGUILayout.IntField("MergedRegionSize", m_buildSetting.MergedRegionSize, new GUILayoutOption[0]);
                if (tmpMergeRegionArea >= 0f && tmpMergeRegionArea != m_buildSetting.MergedRegionSize)
                {
                    m_buildSetting.MergedRegionSize = tmpMergeRegionArea;
                }
            }

            //NavMesh
            EditorGUILayout.Space();
            EditorGUILayout.LabelField(new GUIContent("NavMesh"), EditorStyles.boldLabel, new GUILayoutOption[0]);
            using (new EditorGUILayout.VerticalScope())
            {
                // MaxEdgeLength
                EditorGUILayout.Space();
                int tmpMaxEdgeLength = EditorGUILayout.IntField("MaxEdgeLength", m_buildSetting.MaxEdgeLength, new GUILayoutOption[0]);
                if (tmpMaxEdgeLength >= 0f && tmpMaxEdgeLength != m_buildSetting.MergedRegionSize)
                {
                    m_buildSetting.MaxEdgeLength = tmpMaxEdgeLength;
                }

                // MaxEdgeError
                EditorGUILayout.Space();
                m_buildSetting.MaxEdgeError = EditorGUILayout.FloatField("MaxEdgeError", m_buildSetting.MaxEdgeError, new GUILayoutOption[0]);

                EditorGUILayout.Space();
                m_buildSetting.SampleDistance = EditorGUILayout.IntField("SampleDistance", m_buildSetting.SampleDistance, new GUILayoutOption[0]);

                EditorGUILayout.Space();
                m_buildSetting.MaxSampleError = EditorGUILayout.IntField("MaxSampleError", m_buildSetting.MaxSampleError, new GUILayoutOption[0]);

                EditorGUILayout.Space();
                m_buildSetting.VertsPerPoly = EditorGUILayout.IntField("VertsPerPoly", m_buildSetting.VertsPerPoly, new GUILayoutOption[0]);

                EditorGUILayout.Space();
                m_buildSetting.BuildBoundingVolumeTree = EditorGUILayout.Toggle("BuildBoundingVolumeTree", m_buildSetting.BuildBoundingVolumeTree, new GUILayoutOption[0]);

            }

            // Apply Setting
            EditorGUILayout.Space();
            using (new EditorGUILayout.HorizontalScope())
            {

                if (GUILayout.Button("Apply Setting"))
                {
                    // 跟场景有关
                }

                EditorGUILayout.Space();
            }
        }

        // Bake NavMesh
        EditorGUILayout.Space();
        EditorGUILayout.Space();
        m_step3 = EditorGUILayout.Toggle(new GUIContent("Setp 3 : Bake NavMesh"), m_step3, EditorStyles.foldout, new GUILayoutOption[0]);
        if (m_step3)
        {
            using (new EditorGUILayout.HorizontalScope())
            {
                if (GUILayout.Button("Bake"))
                {
                    m_tiledNavMesh = SharpNavTool.BakeSharpNave(UnityNavMeshTool.SceneBuildingRootName, m_buildSetting);
                    if (m_navDrawer!=null)
                    {
                        m_navDrawer.SetNavMesh(m_tiledNavMesh, m_buildSetting.VertsPerPoly);
                    }
                }

                EditorGUILayout.Space();

                if (GUILayout.Button("Clear"))
                {
                    m_tiledNavMesh = null;
                    if (m_navDrawer != null)
                    {
                        m_navDrawer.SetNavMesh(m_tiledNavMesh, m_buildSetting.VertsPerPoly);
                    }
                }

            }
        }

        // Export NavMesh
        EditorGUILayout.Space();
        EditorGUILayout.Space();
        m_step4 = EditorGUILayout.Toggle(new GUIContent("Setp 4 : Export NavMesh"), m_step4, EditorStyles.foldout, new GUILayoutOption[0]);
        if (m_step4)
        {
            using (new EditorGUILayout.HorizontalScope())
            {
                if (GUILayout.Button("Export"))
                {
                    /*
                    if (m_tiledNavMesh==null)
                        m_tiledNavMesh = SharpNavTool.BakeSharpNavWithArea(UnityNavMeshTool.SceneBuildingRootName, m_buildSetting);

                    if (m_tiledNavMesh!=null)
                        SharpNavTool.ExportCurrentSceneSharpNav(m_tiledNavMesh);
                    */
                    m_tiledNavMesh = SharpNavTool.ExportSharpNavMesh();
                    if (m_navDrawer != null)
                    {
                        m_navDrawer.SetNavMesh(m_tiledNavMesh, m_buildSetting.VertsPerPoly);
                    }
                }
            }
        }

        EditorGUILayout.Space();
        EditorGUILayout.Space();
    }

    // Update is called once per frame
    void Update()
    {

    }
	
}
