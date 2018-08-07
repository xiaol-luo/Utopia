using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DemoInit : MonoBehaviour {
    public Moba_Camera moba_camera = null;
    // Use this for initialization
    void Start () {
        var boundaries = GameObject.FindObjectsOfType<Moba_Camera_Boundary>();
        foreach (var item in boundaries)
        {
            moba_camera.cameraBoundaries.AddBoundary(item);
        }
	}
}
