
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
        private NavMeshBuilder buildData;
        private TiledNavMesh tiledNavMesh;
        private NavMeshQuery navMeshQuery;
        private Color[] regionColors;

        public bool isDrawMesh = true;
        public bool isDraw = true;
        private List<Mesh> drawMeshs = new List<Mesh>();

        public float test = 1.0f;

        SharpNav.Geometry.Vector3 ConvertVector3(UnityEngine.Vector3 vector3)
        {
            return new SharpNav.Geometry.Vector3(vector3.x, vector3.y, vector3.z);
        }
        UnityEngine.Vector3 ConvertVector3(SharpNav.Geometry.Vector3 vector3)
        {
            return new UnityEngine.Vector3(vector3.X, vector3.Y, vector3.Z);
        }

        public void GenNavMesh()
        {
            // MeshCollider
            List<Triangle3> colliderTringles = new List<Triangle3>();
            Collider[] colliders = GameObject.FindObjectsOfType<Collider>();
            List<GameObject> destroyGos = new List<GameObject>();
            foreach (Collider collider in colliders)
            {
                Mesh mesh = null;
                Matrix4x4 localToWorldMatrix = Matrix4x4.identity;

                if (collider is MeshCollider)
                {
                    MeshCollider mc = collider as MeshCollider;
                    mesh = mc.sharedMesh;
                    localToWorldMatrix = mc.transform.localToWorldMatrix;
                }
                if (collider is BoxCollider)
                {
                    BoxCollider bc = collider as BoxCollider;
                    GameObject go = GameObject.CreatePrimitive(PrimitiveType.Cube);
                    mesh = go.GetComponent<MeshFilter>().sharedMesh;
                    go.transform.parent = collider.transform;
                    go.transform.localRotation = Quaternion.identity;
                    go.transform.localPosition = bc.center;
                    go.transform.localScale = bc.size;
                    localToWorldMatrix = go.transform.localToWorldMatrix;
                    destroyGos.Add(go);
                }
                if (null != mesh)
                {
                    UnityEngine.Vector3[] vertices = mesh.vertices;
                    for (int i = 0; i < mesh.subMeshCount; ++i)
                    {
                        var subMesh = mesh.GetIndices(i);
                        for (int j = 0; j < subMesh.Length; j += 3)
                        {
                            UnityEngine.Vector3 a = localToWorldMatrix.MultiplyPoint(vertices[subMesh[j]]);
                            UnityEngine.Vector3 b = localToWorldMatrix.MultiplyPoint(vertices[subMesh[j + 1]]);
                            UnityEngine.Vector3 c = localToWorldMatrix.MultiplyPoint(vertices[subMesh[j + 2]]);
                            colliderTringles.Add(new Triangle3(ConvertVector3(a), ConvertVector3(b), ConvertVector3(c)));
                        }
                    }
                }
            }
            foreach (var go in destroyGos)
            {
                GameObject.DestroyImmediate(go);
            }
            destroyGos.Clear();

            Triangle3[] levelTris = colliderTringles.ToArray();
            var triEnumerable = TriangleEnumerable.FromTriangle(levelTris, 0, levelTris.Length);
            BBox3 bounds = triEnumerable.GetBoundingBox();
            heightfield = new Heightfield(bounds, settings);
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
            buildData = new NavMeshBuilder(polyMesh, polyMeshDetail, new SharpNav.Pathfinding.OffMeshConnection[0], settings);
            tiledNavMesh = new TiledNavMesh(buildData);
            navMeshQuery = new NavMeshQuery(tiledNavMesh, 2048);

            {
                System.Random r = new System.Random();
                regionColors = new Color[compactHeightfield.MaxRegions];
                regionColors[0] = Color.black;
                for (int i = 1; i < regionColors.Length; i++)
                    regionColors[i] = new Color((byte)r.Next(0, 255), (byte)r.Next(0, 255), (byte)r.Next(0, 255), 255);
            }

            {
                drawMeshs.Clear();
                var tile = tiledNavMesh.GetTileAt(0, 0, 0);
                if (null != tile)
                {
                    for (int i = 0; i < tile.Polys.Length; i++)
                    {
                        Mesh mesh = new Mesh();
                        drawMeshs.Add(mesh);
                        {
                            List<UnityEngine.Vector3> vertices = new List<UnityEngine.Vector3>();
                            List<int> triangles = new List<int>();
                            for (int j = 0; j < settings.VertsPerPoly; ++j)
                            {
                                int vertIndex = tile.Polys[i].Verts[j];
                                if (0 == vertIndex)
                                    break;
                                vertices.Add(ConvertVector3(tile.Verts[vertIndex]));
                            }
                            mesh.vertices = vertices.ToArray();

                            int idx_1 = 1;
                            int idx_2 = 2;
                            while (idx_2 < mesh.vertices.Length)
                            {
                                triangles.Add(0);
                                triangles.Add(idx_1);
                                triangles.Add(idx_2);
                                ++idx_1;
                                ++idx_2;
                            }
                            mesh.triangles = triangles.ToArray();
                            Gizmos.color = Color.green;
                            mesh.RecalculateNormals();
                            mesh.RecalculateBounds();
                        }
                    }
                }
            }

            Debug.Log("GenNavMesh Done!");
        }

        public void OnDrawGizmos()
        {
            if (null != tiledNavMesh)
            {
                var tile = tiledNavMesh.GetTileAt(0, 0, 0);
                if (null != tile)
                {
                    for (int i = 0; i < tile.Polys.Length; i++)
                    {

                    }
                }
            }


            if (isDraw)
            {
                Color oldColor = Gizmos.color;

                foreach (var mesh in drawMeshs)
                {
                    if (isDrawMesh)
                    {
                        Gizmos.color = Color.green;
                        Gizmos.DrawMesh(mesh);
                    }
                    if (mesh.vertices.Length > 0)
                    {
                        Gizmos.color = Color.yellow;
                        for (int j = 1; j < mesh.vertices.Length; ++j)
                        {
                            Gizmos.DrawLine(mesh.vertices[j - 1], mesh.vertices[j]);
                        }
                        Gizmos.DrawLine(mesh.vertices[0], mesh.vertices[mesh.vertices.Length - 1]);

                        Gizmos.color = Color.red;
                        for (int j = 0; j < mesh.vertices.Length; ++j)
                        {
                            Gizmos.DrawSphere(mesh.vertices[j], 0.5f);
                        }
                    }
                }

                Gizmos.color = oldColor;
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
