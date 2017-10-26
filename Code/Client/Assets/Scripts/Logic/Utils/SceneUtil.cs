
using UnityEngine;

public static class SceneUtils
{
    const float MouseRaycastDistance = 200.0f;
    public static bool ScreenMouseToGround(Camera camera, Vector3 mousePos, ref Vector3 hitPos)
    {
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
}
