using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEditor.AI;

public class UnityNavMeshEditor : EditorWindow
{

    private SerializedObject m_Object;

    private SerializedProperty m_AgentRadius;

    private SerializedProperty m_AgentHeight;

    private SerializedProperty m_AgentSlope;

    private SerializedProperty m_AgentClimb;

    //private SerializedProperty m_LedgeDropHeight;

    //private SerializedProperty m_MaxJumpAcrossDistance;

    private SerializedProperty m_MinRegionArea;

    private SerializedProperty m_ManualCellSize;

    private SerializedProperty m_CellSize;

    //private SerializedProperty m_AccuratePlacement;

    //private SerializedObject m_NavMeshAreasObject;

    //private SerializedProperty m_Areas;

    private Vector2 m_ScrollPos = Vector2.zero;
    private bool m_step1 = true;
    private bool m_step2 = true;
    private bool m_step3 = true;
    private bool m_step4 = true;


    [MenuItem("Tools/Unity导航网格工具/Unity导航网格编辑工具", false, 100)]
    static void SetupWindow()
    {
        UnityNavMeshEditor window = GetWindow<UnityNavMeshEditor>();
        window.minSize = new Vector2(300, 360);
    }

    public void OnEnable()
    {
        Init();
        Repaint();
    }

    public void OnDisable()
    {

    }

    public void OnGUI()
    {
        using (var sv = new EditorGUILayout.ScrollViewScope(m_ScrollPos))
        {
            m_ScrollPos = sv.scrollPosition;
            BakeSetting();
        }
    }

    void Init()
    {
        this.m_Object = new SerializedObject(NavMeshBuilder.navMeshSettingsObject);
        this.m_AgentRadius = this.m_Object.FindProperty("m_BuildSettings.agentRadius");
        this.m_AgentHeight = this.m_Object.FindProperty("m_BuildSettings.agentHeight");
        this.m_AgentSlope = this.m_Object.FindProperty("m_BuildSettings.agentSlope");
        this.m_AgentClimb = this.m_Object.FindProperty("m_BuildSettings.agentClimb");

        this.m_MinRegionArea = this.m_Object.FindProperty("m_BuildSettings.minRegionArea");
        this.m_ManualCellSize = this.m_Object.FindProperty("m_BuildSettings.manualCellSize");
        this.m_CellSize = this.m_Object.FindProperty("m_BuildSettings.cellSize");
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
            using (new EditorGUILayout.VerticalScope())
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

            Rect controlRect = EditorGUILayout.GetControlRect(false, 120f, new GUILayoutOption[0]);
            this.DrawAgentDiagram(controlRect, this.m_AgentRadius.floatValue, this.m_AgentHeight.floatValue, this.m_AgentClimb.floatValue, this.m_AgentSlope.floatValue);

            using (new EditorGUILayout.VerticalScope())
            {
                float num = EditorGUILayout.FloatField("Agent Radius", this.m_AgentRadius.floatValue, new GUILayoutOption[0]);
                if (num >= 0.001f && !Mathf.Approximately(num - this.m_AgentRadius.floatValue, 0f))
                {
                    this.m_AgentRadius.floatValue = num;
                    if (!this.m_ManualCellSize.boolValue)
                    {
                        this.m_CellSize.floatValue = 2f * this.m_AgentRadius.floatValue / 6f;
                    }
                }
                if (this.m_AgentRadius.floatValue < 0.05f && !this.m_ManualCellSize.boolValue)
                {
                    EditorGUILayout.HelpBox("The agent radius you've set is really small, this can slow down the build.\nIf you intended to allow the agent to move close to the borders and walls, please adjust voxel size in advaced settings to ensure correct bake.", MessageType.Warning);
                }
                float num2 = EditorGUILayout.FloatField("Agent Height", this.m_AgentHeight.floatValue, new GUILayoutOption[0]);
                if (num2 >= 0.001f && !Mathf.Approximately(num2 - this.m_AgentHeight.floatValue, 0f))
                {
                    this.m_AgentHeight.floatValue = num2;
                }
                EditorGUILayout.Slider(this.m_AgentSlope, 0f, 60f, "Agent Slope", new GUILayoutOption[0]);
                if (this.m_AgentSlope.floatValue > 60f)
                {
                    EditorGUILayout.HelpBox("The maximum slope should be set to less than " + 60f + " degrees to prevent NavMesh build artifacts on slopes. ", MessageType.Warning);
                }
                float num3 = EditorGUILayout.FloatField("AgentClimb", this.m_AgentClimb.floatValue, new GUILayoutOption[0]);
                if (num3 >= 0f && !Mathf.Approximately(this.m_AgentClimb.floatValue - num3, 0f))
                {
                    this.m_AgentClimb.floatValue = num3;
                }
                if (this.m_AgentClimb.floatValue > this.m_AgentHeight.floatValue)
                {
                    EditorGUILayout.HelpBox("Step height should be less than agent height.\nClamping step height to " + this.m_AgentHeight.floatValue + " internally when baking.", MessageType.Warning);
                }
                // 判断爬坡高度和斜坡角度是否超过其极限值
                float cellSize = this.m_CellSize.floatValue;
                float halfCellSize = cellSize * 0.5f;
                int climbVal = (int)Mathf.Ceil(this.m_AgentClimb.floatValue / halfCellSize);
                float slopeTan = Mathf.Tan(this.m_AgentSlope.floatValue / 180f * Mathf.PI) * cellSize;
                int slopeVal = (int)Mathf.Ceil(slopeTan * 2f / halfCellSize);
                if (slopeVal > climbVal)
                {
                    float f = (float)climbVal * halfCellSize / (cellSize * 2f);
                    float num8 = Mathf.Atan(f) / Mathf.PI * 180f;
                    float num9 = (float)(slopeVal - 1) * halfCellSize;
                    EditorGUILayout.HelpBox(string.Concat(new string[]
				{
					"Step Height conflicts with Max Slope. This makes some slopes unwalkable.\nConsider decreasing Max Slope to < ",
					num8.ToString("0.0"),
					" degrees.\nOr, increase Step Height to > ",
					num9.ToString("0.00"),
					"."
				}), MessageType.Warning);
                }
            }

            // Advance
            EditorGUILayout.Space();
            EditorGUILayout.LabelField(new GUIContent("Advance"), EditorStyles.boldLabel, new GUILayoutOption[0]);

            using (new EditorGUILayout.VerticalScope())
            {
                bool flag = EditorGUILayout.Toggle("Manual Voxel Size", this.m_ManualCellSize.boolValue, new GUILayoutOption[0]);
                if (flag != this.m_ManualCellSize.boolValue)
                {
                    this.m_ManualCellSize.boolValue = flag;
                    if (!flag)
                    {
                        this.m_CellSize.floatValue = 2f * this.m_AgentRadius.floatValue / 6f;
                    }
                }

                using (new EditorGUI.DisabledScope(!this.m_ManualCellSize.boolValue))
                {
                    float tempCellSize = EditorGUILayout.FloatField("CellSize", this.m_CellSize.floatValue, new GUILayoutOption[0]);
                    if (tempCellSize > 0f && !Mathf.Approximately(tempCellSize - this.m_CellSize.floatValue, 0f))
                    {
                        this.m_CellSize.floatValue = Mathf.Max(0.01f, tempCellSize);
                    }
                    if (tempCellSize < 0.01f)
                    {
                        EditorGUILayout.HelpBox("The voxel size should be larger than 0.01.", MessageType.Warning);
                    }
                    float tempRadius = (this.m_CellSize.floatValue <= 0f) ? 0f : (this.m_AgentRadius.floatValue / this.m_CellSize.floatValue);
                    EditorGUILayout.LabelField(" ", tempRadius.ToString("0.00") + " voxels per agent radius", EditorStyles.miniLabel, new GUILayoutOption[0]);
                    if (this.m_ManualCellSize.boolValue)
                    {
                        float hCellSize = this.m_CellSize.floatValue * 0.5f;
                        if ((int)Mathf.Floor(this.m_AgentHeight.floatValue / hCellSize) > 250)
                        {
                            EditorGUILayout.HelpBox("The number of voxels per agent height is too high. This will reduce the accuracy of the navmesh. Consider using voxel size of at least " + (this.m_AgentHeight.floatValue / 250f / 0.5f).ToString("0.000") + ".", MessageType.Warning);
                        }
                        if (tempRadius < 1f)
                        {
                            EditorGUILayout.HelpBox("The number of voxels per agent radius is too small. The agent may not avoid walls and ledges properly. Consider using voxel size of at least " + (this.m_AgentRadius.floatValue / 2f).ToString("0.000") + " (2 voxels per agent radius).", MessageType.Warning);
                        }
                        else if (tempRadius > 8f)
                        {
                            EditorGUILayout.HelpBox("The number of voxels per agent radius is too high. It can cause excessive build times. Consider using voxel size closer to " + (this.m_AgentRadius.floatValue / 8f).ToString("0.000") + " (8 voxels per radius).", MessageType.Warning);
                        }
                    }
                    if (this.m_ManualCellSize.boolValue)
                    {
                        EditorGUILayout.HelpBox("Voxel size controls how accurately the navigation mesh is generated from the level geometry. A good voxel size is 2-4 voxels per agent radius. Making voxel size smaller will increase build time.", MessageType.None);
                    }
                }

                // MinRegionArea
                EditorGUILayout.Space();
                float tmpMinRegionArea = EditorGUILayout.FloatField("MinRegionArea", this.m_MinRegionArea.floatValue, new GUILayoutOption[0]);
                if (tmpMinRegionArea >= 0f && tmpMinRegionArea != this.m_MinRegionArea.floatValue)
                {
                    this.m_MinRegionArea.floatValue = tmpMinRegionArea;
                }
            }

            // Apply Setting
            EditorGUILayout.Space();
            using (new EditorGUILayout.VerticalScope())
            {

                if (GUILayout.Button("Apply Setting"))
                {
                    this.m_Object.ApplyModifiedProperties();
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
            using (new EditorGUILayout.VerticalScope())
            {
                if (GUILayout.Button("Bake"))
                {
                    UnityNavMeshTool.BakeUnityNavMesh(UnityNavMeshTool.SceneBuildingRootName);
                }

                EditorGUILayout.Space();
            }
        }

        // Export NavMesh
        EditorGUILayout.Space();
        EditorGUILayout.Space();
        m_step4 = EditorGUILayout.Toggle(new GUIContent("Setp 4 : Export NavMesh"), m_step4, EditorStyles.foldout, new GUILayoutOption[0]);
        if (m_step4)
        {
            using (new EditorGUILayout.VerticalScope())
            {
                if (GUILayout.Button("Export .josn"))
                {
                    UnityNavMeshTool.GenUnityNavMesh(0);
                }

                if (GUILayout.Button("Export .obj"))
                {
                    UnityNavMeshTool.GenUnityNavMesh(1);
                }
            }
        }

        EditorGUILayout.Space();
        EditorGUILayout.Space();
    }

    private void DrawAgentDiagram(Rect rect, float agentRadius, float agentHeight, float agentClimb, float agentSlope)
    {
        if (Event.current.type != EventType.Repaint)
        {
            return;
        }
        float num = 0.35f;
        float num2 = 15f;
        float num3 = rect.height - num2 * 2f;
        float num4 = Mathf.Min(num3 / (agentHeight + agentRadius * 2f * num), num3 / (agentRadius * 2f));
        float num5 = agentHeight * num4;
        float num6 = agentRadius * num4;
        float num7 = agentClimb * num4;
        float num8 = rect.xMin + rect.width * 0.5f;
        float num9 = rect.yMax - num2 - num6 * num;
        Vector3[] array = new Vector3[40];
        Vector3[] array2 = new Vector3[20];
        Vector3[] array3 = new Vector3[20];
        for (int i = 0; i < 20; i++)
        {
            float f = (float)i / 19f * 3.14159274f;
            float num10 = Mathf.Cos(f);
            float num11 = Mathf.Sin(f);
            array[i] = new Vector3(num8 + num10 * num6, num9 - num5 - num11 * num6 * num, 0f);
            array[i + 20] = new Vector3(num8 - num10 * num6, num9 + num11 * num6 * num, 0f);
            array2[i] = new Vector3(num8 - num10 * num6, num9 - num5 + num11 * num6 * num, 0f);
            array3[i] = new Vector3(num8 - num10 * num6, num9 - num7 + num11 * num6 * num, 0f);
        }
        Color color = Handles.color;
        float xMin = rect.xMin;
        float num12 = num9 - num7;
        float num13 = num8 - num3 * 0.75f;
        float y = num9;
        float num14 = num8 + num3 * 0.75f;
        float num15 = num9;
        float num16 = num14;
        float num17 = num15;
        float num18 = rect.xMax - num14;
        num16 += Mathf.Cos(agentSlope * 0.0174532924f) * num18;
        num17 -= Mathf.Sin(agentSlope * 0.0174532924f) * num18;
        Vector3[] points = new Vector3[]
			{
				new Vector3(xMin, num9, 0f),
				new Vector3(num16, num9, 0f)
			};
        Vector3[] points2 = new Vector3[]
			{
				new Vector3(xMin, num12, 0f),
				new Vector3(num13, num12, 0f),
				new Vector3(num13, y, 0f),
				new Vector3(num14, num15, 0f),
				new Vector3(num16, num17, 0f)
			};
        Handles.color = ((!EditorGUIUtility.isProSkin) ? new Color(1f, 1f, 1f, 0.5f) : new Color(0f, 0f, 0f, 0.5f));
        Handles.DrawAAPolyLine(2f, points);
        Handles.color = ((!EditorGUIUtility.isProSkin) ? new Color(0f, 0f, 0f, 0.5f) : new Color(1f, 1f, 1f, 0.5f));
        Handles.DrawAAPolyLine(3f, points2);
        Handles.color = Color.Lerp(new Color(0f, 0.75f, 1f, 1f), new Color(0.5f, 0.5f, 0.5f, 0.5f), 0.2f);
        Handles.DrawAAConvexPolygon(array);
        Handles.color = new Color(0f, 0f, 0f, 0.5f);
        Handles.DrawAAPolyLine(2f, array3);
        Handles.color = new Color(1f, 1f, 1f, 0.4f);
        Handles.DrawAAPolyLine(2f, array2);
        Vector3[] points3 = new Vector3[]
			{
				new Vector3(num8, num9 - num5, 0f),
				new Vector3(num8 + num6, num9 - num5, 0f)
			};
        Handles.color = new Color(0f, 0f, 0f, 0.5f);
        Handles.DrawAAPolyLine(2f, points3);
        GUI.Label(new Rect(num8 + num6 + 5f, num9 - num5 * 0.5f - 10f, 150f, 20f), string.Format("H = {0}", agentHeight));
        GUI.Label(new Rect(num8, num9 - num5 - num6 * num - 15f, 150f, 20f), string.Format("R = {0}", agentRadius));
        GUI.Label(new Rect((xMin + num13) * 0.5f - 20f, num12 - 15f, 150f, 20f), string.Format("{0}", agentClimb));
        GUI.Label(new Rect(num14 + 20f, num15 - 15f, 150f, 20f), string.Format("{0}°", agentSlope));
        Handles.color = color;
    }

    // Update is called once per frame
    void Update()
    {

    }
}
