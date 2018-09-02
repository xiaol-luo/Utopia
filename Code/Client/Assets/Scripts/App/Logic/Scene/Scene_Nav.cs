using NetProto;
using SharpNav.IO.Json;
using System.Collections.Generic;
using System.IO;
using SharpNav.Pathfinding;

namespace Utopia
{
    public partial class Scene
    {
        SharpNav.TiledNavMesh m_navMesh;
        public SharpNav.TiledNavMesh navMesh { get { return m_navMesh; } }
        SharpNav.NavMeshQuery m_navQuery;
        public SharpNav.NavMeshQuery navQuery { get { return m_navQuery; } }

        void LoadNavMesh()
        {
            var nms = new NavMeshJsonSerializer();
            string navFilePath = System.IO.Path.Combine(UnityEngine.Application.dataPath, "Resources/Levels/Level_Battle/Level_Battle.snb");
            m_navMesh = nms.Deserialize(navFilePath);
            m_navQuery = new SharpNav.NavMeshQuery(m_navMesh, 256);
        }

        #region 寻路
        // NPC
        SharpNav.Geometry.Vector3 DeaultSharpNavExtend = new SharpNav.Geometry.Vector3(0.1f, 0.1f, 0.1f);
        public NavPoint FindNearestNavPoint(UnityEngine.Vector3 position)
        {
            return navQuery.FindNearestPoly(new SharpNav.Geometry.Vector3(position.x, position.y, position.z), DeaultSharpNavExtend);
        }

        public NavPoint FindNearestNavPoint(UnityEngine.Vector3 center, UnityEngine.Vector3 extents)
        {
            return navQuery.FindNearestPoly(
                new SharpNav.Geometry.Vector3(center.x, center.y, center.z),
                new SharpNav.Geometry.Vector3(extents.x, extents.y, extents.z));
        }

        public bool IsPointsConnected(UnityEngine.Vector3 from, UnityEngine.Vector3 to)
        {
            NavPoint fromNavPoint = navQuery.FindNearestPoly(new SharpNav.Geometry.Vector3(from.x, from.y, from.z), DeaultSharpNavExtend);
            if (NavPolyId.Null == fromNavPoint.Polygon)
                return false;
            NavPoint toNavPoint = navQuery.FindNearestPoly(new SharpNav.Geometry.Vector3(to.x, to.y, to.z), DeaultSharpNavExtend);
            if (NavPolyId.Null == toNavPoint.Polygon)
                return false;
            if (fromNavPoint.Polygon == toNavPoint.Polygon)
                return true;

            HashSet<NavPolyId> checkedPolyIds = new HashSet<NavPolyId>();
            Queue<NavPolyId> waitCheckPolyIds = new Queue<NavPolyId>();

            waitCheckPolyIds.Enqueue(fromNavPoint.Polygon);
            while (waitCheckPolyIds.Count > 0)
            {
                NavPolyId polyId = waitCheckPolyIds.Dequeue();
                checkedPolyIds.Add(polyId);

                NavTile tile; NavPoly poly;
                if (!navMesh.TryGetTileAndPolyByRef(polyId, out tile, out poly))
                    break;

                foreach (Link link in poly.Links)
                {
                    if (link.Reference == toNavPoint.Polygon)
                        return true;
                    if (link.Reference == NavPolyId.Null)
                        continue;
                    if (!checkedPolyIds.Contains(link.Reference))
                        waitCheckPolyIds.Enqueue(link.Reference);
                }
            }

            return false;
        }

        //射线失败就直接返回起始点
        public UnityEngine.Vector3 Recast(UnityEngine.Vector3 start, UnityEngine.Vector3 end)
        {
            UnityEngine.Vector3 ret = start;
            NavPoint startPoint = FindNearestNavPoint(start);
            if (NavPolyId.Null != startPoint.Polygon)
            {
                SharpNav.Geometry.Vector3 endPoint = new SharpNav.Geometry.Vector3(end.x, end.y, end.z);
                RaycastHit hit; SharpNav.Pathfinding.Path path = new SharpNav.Pathfinding.Path();
                if (navQuery.Raycast(ref startPoint, ref endPoint, RaycastOptions.None, out hit, path))
                {
                    if (hit.IsHit)
                    {
                        ret = start + (end - start) * hit.T;
                    }
                    else
                    {
                        ret = end;
                    }
                }
            }
            return ret;
        }

        public List<UnityEngine.Vector3> FindPath(UnityEngine.Vector3 start, UnityEngine.Vector3 end)
        {
            var startPoint = FindNearestNavPoint(start);
            if (NavPolyId.Null == startPoint.Polygon)
                return null;

            var endPoint = FindNearestNavPoint(end);
            if (NavPolyId.Null == endPoint.Polygon)
                return null;

            List<SharpNav.Geometry.Vector3> points = new List<SharpNav.Geometry.Vector3>();
            SharpNav.Utility.FindPath(navQuery, startPoint, endPoint, points, 2048);

            List<UnityEngine.Vector3> ps = new List<UnityEngine.Vector3>();
            for (int i = 0; i < points.Count; ++i)
            {
                var p = points[i];
                ps.Add(new UnityEngine.Vector3(p.X, p.Y, p.Z));
            }
            return ps;
        }

        // Use For Verify Path
        public List<List<UnityEngine.Vector3>> FindPathPolys(UnityEngine.Vector3 start, UnityEngine.Vector3 end)
        {
            var startPoint = FindNearestNavPoint(start);
            if (NavPolyId.Null != startPoint.Polygon)
                return null;
            var endPoint = FindNearestNavPoint(end);
            if (NavPolyId.Null != endPoint.Polygon)
                return null;

            SharpNav.Pathfinding.Path path = new SharpNav.Pathfinding.Path();
            bool ret = navQuery.FindPath(ref startPoint, ref endPoint, new NavQueryFilter(), path);
            if (!ret)
                return null;

            List<List<UnityEngine.Vector3>> polys = new List<List<UnityEngine.Vector3>>();
            {
                List<NavPolyId> relatePolys = new List<NavPolyId>();
                relatePolys.Add(startPoint.Polygon);
                for (int i = 0; i < path.Count; ++i)
                {
                    relatePolys.Add(path[i]);
                }
                relatePolys.Add(endPoint.Polygon);
                for (int i = 0; i < relatePolys.Count; ++i)
                {
                    NavPolyId polyId = relatePolys[i];
                    NavTile tile; NavPoly poly;
                    if (navMesh.TryGetTileAndPolyByRef(polyId, out tile, out poly))
                    {
                        List<UnityEngine.Vector3> polyVerts = new List<UnityEngine.Vector3>();
                        polys.Add(polyVerts);
                        for (int j = 0; j < poly.VertCount; ++j)
                        {
                            SharpNav.Geometry.Vector3 p = tile.Verts[poly.Verts[j]];
                            polyVerts.Add(new UnityEngine.Vector3() { x = p.X, y = p.Y, z = p.Z });
                        }
                    }
                }
            }
            return polys;
        }
        #endregion
    }
}
