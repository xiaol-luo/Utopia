
using UnityEngine;

public static class SceneUtils
{
    const float MouseRaycastDistance = 200.0f;
    public static bool ScreenToGround(Camera camera, Vector3 mousePos, ref Vector3 hitPos)
    {
        if (null == camera)
            return false;

        Ray ray = camera.ScreenPointToRay(mousePos);
        RaycastHit[] hitList = Physics.RaycastAll(ray, MouseRaycastDistance, LayerUtil.groundMask);
        bool isOk = false;
        if (null != hitList && hitList.Length > 0)
        {
            isOk = true;
            RaycastHit hit = hitList[0];
            hitPos = hit.point;
        }
        return isOk;
    }

    public static GameObject ScreenToSceneObject(Camera camera, Vector3 mousePos)
    {
        if (null == camera)
            return null;

        Ray ray = camera.ScreenPointToRay(mousePos);
        RaycastHit[] hitList = Physics.RaycastAll(ray, MouseRaycastDistance, LayerUtil.groundMask);
        GameObject go = null;
        if (null != hitList && hitList.Length > 0)
        {
            RaycastHit hit = hitList[0];
            go = hit.collider.gameObject;
        }
        return go;
    }
}
