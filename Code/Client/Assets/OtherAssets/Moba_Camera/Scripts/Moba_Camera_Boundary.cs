using UnityEngine;
using System.Collections;
/*
 * On Start adds self to the list of boundaries in the scene.
 * - Remove having to drag and drop each indiviual boundary.
 */
public class Moba_Camera_Boundary : MonoBehaviour {
    public bool isActive = true;
    public Moba_Camera_Boundaries.BoundaryType type { get; protected set; }

    private void Awake()
    {
        type = Moba_Camera_Boundaries.BoundaryType.none;
        Collider collider = this.GetComponent<Collider>();
        if (null != collider)
        {
            if (collider is BoxCollider)
            {
                type = Moba_Camera_Boundaries.BoundaryType.cube;
            }
            if (collider is SphereCollider)
            {
                type = Moba_Camera_Boundaries.BoundaryType.sphere;
            }
        }
    }
}
