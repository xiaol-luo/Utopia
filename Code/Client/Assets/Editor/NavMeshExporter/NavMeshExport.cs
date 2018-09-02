using UnityEngine;
using UnityEditor;
using System.Collections;
using System.IO;

using UnityEditor.SceneManagement;
using System.Collections.Generic;
using SharpNav;

namespace CustomEditor
{
	class NavMeshExport
	{
		const float BaseOffset = -0.12f;

		[MenuItem("Tools/RecastNav/新建区域")]
		static void CreateNewArea()
		{
			GameObject root = GameObject.Find("GeomSet");
			if (root == null)
				root = new GameObject("GeomSet");
			GameObject go = new GameObject("Spline");
			go.transform.SetParent(root.transform);
			Spline spline = go.AddComponent<Spline>();
			float s = 3;
			Rect rect = new Rect(-s * 0.5f, -s * 0.5f, s, s);
			spline.AddNode(new Vector3(rect.xMin, 0, rect.yMin));
			spline.AddNode(new Vector3(rect.xMax, 0, rect.yMin));
			spline.AddNode(new Vector3(rect.xMax, 0, rect.yMax));
			spline.AddNode(new Vector3(rect.xMin, 0, rect.yMax));
			Selection.activeGameObject = go;
			EditorSceneManager.MarkSceneDirty(EditorSceneManager.GetActiveScene()); // Mark need save
		}

		[MenuItem("Tools/RecastNav/Export NavMesh")]
		public static void ExportNavmesh()
		{
            string objPath = "eos_navmesh.obj";
            Vector3 maxVec = new Vector3(float.MinValue, float.MinValue, float.MinValue);
            Vector3 minVec = new Vector3(float.MaxValue, float.MaxValue, float.MaxValue);
            {
                Vector3[] vs;
                int[] ids;
                string txt = "";

                UnityEngine.AI.NavMeshTriangulation tri = UnityEngine.AI.NavMesh.CalculateTriangulation();
                vs = tri.vertices;
                ids = tri.indices;

                foreach (Vector3 v in vs)
                {
                    float y = v.y + BaseOffset;
                    // EosHack : 
                    //txt += "v " + (v.x) + " " + (v.y) + " " + (v.z) + "\n";
                    txt += "v " + (v.x) + " " + (y) + " " + (v.z) + "\n";

                    minVec.x = v.x < minVec.x ? v.x : minVec.x;
                    minVec.y = y < minVec.y ? y : minVec.y;
                    minVec.z = v.z < minVec.z ? v.z : minVec.z;

                    maxVec.x = v.x > maxVec.x ? v.x : maxVec.x;
                    maxVec.y = y > maxVec.y ? y : maxVec.y;
                    maxVec.z = v.z > maxVec.z ? v.z : maxVec.z;
                }
                for (int i = 0; i < ids.Length; i += 3)
                {
                    txt += "f " + (ids[i] + 1) + " " + (ids[i + 1] + 1) + " " + (ids[i + 2] + 1) + "\n";
                }

                string outFile = Path.Combine(Application.dataPath, "..", objPath);
                File.WriteAllText(outFile, txt);
            }

            {
                {
                    string text = string.Format("f {0}\n", objPath);
                    GameObject root = GameObject.Find("GeomSet");
                    if (root)
                    {
                        int count = root.transform.childCount;
                        for (int i = 0; i < count; i++)
                        {
                            Spline spline = root.transform.GetChild(i).GetComponent<Spline>();
                            int node_count = spline.transform.childCount;
                            Vector3 pos = spline.transform.GetChild(0).position;
                            text += string.Format("v {0} {1} {2} {3}\n", node_count, (int)spline.area, spline.hmin + pos.y, spline.hmax + pos.y);
                            for (int j = 0; j < node_count; ++j)
                            {
                                pos = spline.transform.GetChild(j).position;
                                text += string.Format("{0} {1} {2}\n", pos.x, pos.y, pos.z);
                            }
                        }
                    }

                    List<string> settingStrs = new List<string>();
                    NavMeshGenerationSettings setting = NavMeshGenerationSettings.Default;
                    settingStrs.Add(setting.CellSize.ToString());
                    settingStrs.Add(setting.CellHeight.ToString());
                    settingStrs.Add(setting.AgentHeight.ToString());
                    settingStrs.Add(setting.AgentRadius.ToString());
                    settingStrs.Add(setting.MaxClimb.ToString());

                    settingStrs.Add("45"); // Agent max slope in degrees

                    settingStrs.Add(setting.MinRegionSize.ToString());
                    settingStrs.Add(setting.MergedRegionSize.ToString());
                    settingStrs.Add(setting.MaxEdgeLength.ToString());
                    settingStrs.Add(setting.MaxEdgeError.ToString());

                    settingStrs.Add(setting.VertsPerPoly.ToString());
                    settingStrs.Add(setting.SampleDistance.ToString());
                    settingStrs.Add(setting.MaxSampleError.ToString());
                    settingStrs.Add("0"); // SamplePartitionType

                    // Bounds of the area to mesh
                    settingStrs.Add(minVec.x.ToString()); // min_x
                    settingStrs.Add(minVec.y.ToString()); // min_y
                    settingStrs.Add(minVec.z.ToString()); // min_z

                    settingStrs.Add(maxVec.x.ToString()); // max_x
                    settingStrs.Add(maxVec.y.ToString()); // max_y
                    settingStrs.Add(maxVec.z.ToString()); // max_z

                    settingStrs.Add("32"); // tile size

                    text += "s";
                    foreach (string item in settingStrs)
                    {
                        text += string.Format(" {0}", item);
                    }
                    text += "\n";

                    string settingPath = Path.Combine(Application.dataPath, "..", "eos_navmesh.gset");
                    File.WriteAllText(settingPath, text);
                }
            }

            EditorUtility.DisplayDialog("提示", "文件保存Ok", "ok", "");
		}
	}
}