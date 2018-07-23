using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace Utopia
{
    class SceneCamera
    {
        public Moba_Camera mobaCamera { get; protected set; }
        public Camera camera
        {
            get
            {
                Camera ret = null;
                if (null != mobaCamera)
                    ret = mobaCamera.GetCamera();
                return ret;
            }
        }

        public void InitCamera()
        {
            mobaCamera = UnityEngine.Object.FindObjectOfType<Moba_Camera>();
            if (null != mobaCamera)
            {
                var cameraBoundaries = UnityEngine.Object.FindObjectsOfType<Moba_Camera_Boundary>();
                foreach (var item in cameraBoundaries)
                {
                    mobaCamera.cameraBoundaries.AddBoundary(item);
                }
            }
        }
        public void ReleaseCamera()
        {
            mobaCamera = null;
        }
    }
}
