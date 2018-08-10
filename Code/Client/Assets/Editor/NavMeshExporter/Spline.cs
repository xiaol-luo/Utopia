using UnityEngine;

public class Spline : MonoBehaviour
{
	public float hmin = -1;
	public float hmax = 6;
	public AreaType area;
	public bool m_closed = false;

	public enum AreaType
	{
		Ground,
		Water,
		Grass,
		Count,
	}

	public const int AreaTypeCount = (int)AreaType.Count;

	Color[] AreaColors = new Color[AreaTypeCount]
	{
		Color.white,
		Color.cyan,
		Color.green,
	};

	Color GetAreaColor(int area, float alpha)
	{
		if (area < 0 || area >= AreaTypeCount)
			return Color.white;
		Color color = AreaColors[area];
		color.a = alpha;
		return color;
	}

	public GameObject AddNode(Vector3 pos)
	{
		GameObject go = new GameObject("Node");
		go.AddComponent<SplineNode>();
		go.transform.SetParent(transform);
		go.transform.position = pos;
		return go;
	}

	public GameObject InsertNodeAfter(Transform prev)
	{
		GameObject go = new GameObject("Node");
		go.AddComponent<SplineNode>();

		int i = 0;
		for (; i < transform.childCount; i++)
		{
			if (prev == transform.GetChild(i))
				break;
		}

		if (i + 1 < transform.childCount) // add after
		{
			go.transform.SetParent(transform);
			go.transform.SetSiblingIndex(i + 1);
			Transform next = transform.GetChild(i + 2);
			go.transform.position = Vector3.Lerp(prev.transform.position, next.transform.position, 0.5f);
		}
		else // add prev
		{
			go.transform.SetParent(transform);
			go.transform.SetSiblingIndex(i);
			Transform prev_prev = transform.GetChild(i - 1);
			go.transform.position = Vector3.Lerp(prev_prev.transform.position, prev.transform.position, 0.5f);
		}

		return go;
	}

	[ExecuteInEditMode]
	void OnDrawGizmos()
	{
		Gizmos.DrawIcon(transform.position, "color_cube.png", false);
		Gizmos.color = GetAreaColor((int)area, 1);
		int count = transform.childCount;
		if (count > 1)
		{
			for (int i = 1; i < count; i++)
			{
				DrawLine(transform.GetChild(i - 1).position, transform.GetChild(i).position);
			}

			if (count > 2 && m_closed)
			{
				DrawLine(transform.GetChild(count - 1).position, transform.GetChild(0).position);
			}

			for (int i = 0; i < count; i++)
			{
				Vector3 from = transform.GetChild(i).position;
				Vector3 to = from;
				from.y += hmin;
				to.y += hmax;
				Gizmos.DrawLine(from, to);
			}
		}
	}

	void DrawLine(Vector3 from, Vector3 to)
	{
		Gizmos.DrawLine(from, to);
		from.y += hmin;
		to.y += hmin;
		Gizmos.DrawLine(from, to);
		from.y += hmax - hmin;
		to.y += hmax - hmin;
		Gizmos.DrawLine(from, to);
	}
}
