
using SharpNav;
using SharpNav.Geometry;
using System;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace NavMesh
{
    public class SharpNavGenerator : MonoBehaviour
    {
        private NavMeshGenerationSettings settings = NavMeshGenerationSettings.Default;

        //Generate poly mesh
        private Heightfield heightfield;
        private CompactHeightfield compactHeightfield;
        private ContourSet contourSet;
        private PolyMesh polyMesh;
        private PolyMeshDetail polyMeshDetail;
        private Color[] regionColors;

        public float test = 1.0f;

        const int BoxColliderVecticeCount = 8;
        UnityEngine.Vector3[] GetBoxColliderWorldVertexs(BoxCollider boxcollider)
        {
            var vertices = new UnityEngine.Vector3[BoxColliderVecticeCount];
            //下面4个点
            vertices[0] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(boxcollider.size.x, -boxcollider.size.y, boxcollider.size.z) * 0.5f);
            vertices[1] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(-boxcollider.size.x, -boxcollider.size.y, boxcollider.size.z) * 0.5f);
            vertices[2] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(-boxcollider.size.x, -boxcollider.size.y, -boxcollider.size.z) * 0.5f);
            vertices[3] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(boxcollider.size.x, -boxcollider.size.y, -boxcollider.size.z) * 0.5f);
            //上面4个点
            vertices[4] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(boxcollider.size.x, boxcollider.size.y, boxcollider.size.z) * 0.5f);
            vertices[5] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(-boxcollider.size.x, boxcollider.size.y, boxcollider.size.z) * 0.5f);
            vertices[6] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(-boxcollider.size.x, boxcollider.size.y, -boxcollider.size.z) * 0.5f);
            vertices[7] = boxcollider.transform.TransformPoint(boxcollider.center + new UnityEngine.Vector3(boxcollider.size.x, boxcollider.size.y, -boxcollider.size.z) * 0.5f);
            return vertices;
        }


        // top 0 1 2 3, buttom 4 5 6 7
        List<int[]> boxPolys = new List<int[]>()
        {
            new int[4]{0, 1, 2, 3 }, // top
            new int[4]{4, 5, 6, 7 }, // buttom
            new int[4]{0, 1, 5, 4 }, // left
            new int[4]{3, 2, 6, 7 }, // right
            new int[4]{0, 3, 7, 4 }, // front
            new int[4]{1, 2, 6, 5 }, // back
        };

        List<int[]> boxTriangles = new List<int[]>()
        {
            new int[3]{0, 1, 2},
            new int[3]{0, 2, 3},
            new int[3]{4, 5, 6},
            new int[3]{4, 6, 7},
            new int[3]{0, 1, 5},
            new int[3]{0, 5, 4},
            new int[3]{3, 2, 6},
            new int[3]{3, 6, 7},
            new int[3]{0, 3, 7},
            new int[3]{0, 7, 4},
            new int[3]{1, 2, 6},
            new int[3]{1, 6, 5},
        };

        SharpNav.Geometry.Vector3 ConvertVector3(UnityEngine.Vector3 vector3)
        {
            return new SharpNav.Geometry.Vector3(vector3.x, vector3.y, vector3.z);
        }

        public void GenNavMesh()
        {
            // MeshCollider

            List<Triangle3> colliderTringles = new List<Triangle3>();
            Collider[] colliders = GameObject.FindObjectsOfType<Collider>();
            foreach (Collider collider in colliders)
            {
                if (collider is MeshCollider)
                {
                    MeshCollider mc = collider as MeshCollider;
                    Mesh mesh = mc.sharedMesh;
                }
                if (collider is BoxCollider)
                {
                    BoxCollider bc = collider as BoxCollider;
                    UnityEngine.Vector3[] vertices = GetBoxColliderWorldVertexs(bc);

                    foreach (int[] triangle in boxTriangles)
                    {
                        SharpNav.Geometry.Vector3 a = ConvertVector3(vertices[triangle[0]]);
                        SharpNav.Geometry.Vector3 b = ConvertVector3(vertices[triangle[1]]);
                        SharpNav.Geometry.Vector3 c = ConvertVector3(vertices[triangle[2]]);
                        colliderTringles.Add(new Triangle3(a, b, c));
                    }
                }
            }

            Triangle3[] levelTris = colliderTringles.ToArray();


            var triEnumerable = TriangleEnumerable.FromTriangle(levelTris, 0, levelTris.Length);
            BBox3 bounds = triEnumerable.GetBoundingBox();

            heightfield = new Heightfield(bounds, settings);

            Console.WriteLine("Heightfield");
            heightfield.RasterizeTriangles(levelTris, Area.Default);
            heightfield.FilterLedgeSpans(settings.VoxelAgentHeight, settings.VoxelMaxClimb);
            heightfield.FilterLowHangingWalkableObstacles(settings.VoxelMaxClimb);
            heightfield.FilterWalkableLowHeightSpans(settings.VoxelAgentHeight);
            compactHeightfield = new CompactHeightfield(heightfield, settings);
            compactHeightfield.Erode(settings.VoxelAgentRadius);
            compactHeightfield.BuildDistanceField();
            compactHeightfield.BuildRegions(0, settings.MinRegionSize, settings.MergedRegionSize);
            contourSet = compactHeightfield.BuildContourSet(settings);
            polyMesh = new PolyMesh(contourSet, settings);
            polyMeshDetail = new PolyMeshDetail(polyMesh, compactHeightfield, settings);

            {
                System.Random r = new System.Random();
                regionColors = new Color[compactHeightfield.MaxRegions];
                regionColors[0] = Color.black;
                for (int i = 1; i < regionColors.Length; i++)
                    regionColors[i] = new Color((byte)r.Next(0, 255), (byte)r.Next(0, 255), (byte)r.Next(0, 255), 255);
            }
        }
    }

    [CustomEditor(typeof(SharpNavGenerator))]
    public class SharpNavGeneratorEditor : Editor
    {
        SharpNavGenerator generator;
        public override void OnInspectorGUI()
        {
            generator = target as SharpNavGenerator;

            base.DrawDefaultInspector();
            //将target转化为我们需要的脚本  
            //增加一个按钮  
            if (GUILayout.Button("GenNavMesh"))
            {
                Debug.Log(string.Format("Test Button {0}", generator.test));
                generator.GenNavMesh();
            }
        }
    }
}
