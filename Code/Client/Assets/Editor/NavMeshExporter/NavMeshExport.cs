using UnityEngine;
using UnityEditor;
using System.Collections;
using System.IO;

using UnityEditor.SceneManagement;

namespace CustomEditor
{
	class NavMeshExport
	{
		const float BaseOffset = -0.12f;

		static string GenerateNavToObj()
		{
			Vector3[] vs;
			int[] ids;
			string txt = "";
#if false
			NavMesh.Triangulate(out vs, out ids);
#else
			UnityEngine.AI.NavMeshTriangulation tri = UnityEngine.AI.NavMesh.CalculateTriangulation();
			vs = tri.vertices;
			ids = tri.indices;
#endif

			foreach (Vector3 v in vs)
			{
				// EosHack : 
				//txt += "v " + (v.x) + " " + (v.y) + " " + (v.z) + "\n";
				txt += "v " + (v.x) + " " + (v.y + BaseOffset) + " " + (v.z) + "\n";
			}
			for (int i = 0; i < ids.Length; i += 3)
			{
				txt += "f " + (ids[i] + 1) + " " + (ids[i + 1] + 1) + " " + (ids[i + 2] + 1) + "\n";
			}
			return txt;
		}

		public static string GenerateGeomSet(string objPath)
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
			return text;
		}

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

		// 保存到文件
		public static bool WriteToFile(ref string msg)
		{
			string objPath = "eos_navmesh.obj";
			File.WriteAllText(objPath, GenerateNavToObj());

            string setPath = "eos_navmesh.gset";
			File.WriteAllText(setPath, GenerateGeomSet(objPath));

            return true;
		}

		[MenuItem("Tools/RecastNav/Export NavMesh")]
		public static void ExportNavmesh()
		{
			string msg="";
			var v = WriteToFile(ref msg);
			if (v)
				EditorUtility.DisplayDialog("提示", "文件保存到" + msg, "Ok");
		}
	}
}