using UnityEngine;

public class SplineNode : MonoBehaviour
{
	[ExecuteInEditMode]
	void OnDrawGizmos()
	{
		Gizmos.DrawIcon(transform.position, "green_ball.png", true);
	}
}
