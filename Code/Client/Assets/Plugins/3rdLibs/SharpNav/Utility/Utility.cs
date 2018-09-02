#if UNITY_EDITOR
// Copyright (c) 2013-2016 Robert Rouhani <robert.rouhani@gmail.com> and other contributors (see CONTRIBUTORS file).
// Licensed under the MIT License - https://raw.github.com/Robmaister/SharpNav/master/LICENSE

using System;
using System.Collections.Generic;

using SharpNav.Collections.Generic;
using SharpNav.Geometry;
using SharpNav.Pathfinding;

#if MONOGAME
using Vector3 = Microsoft.Xna.Framework.Vector3;
#elif OPENTK
using Vector3 = OpenTK.Vector3;
#elif SHARPDX
using Vector3 = SharpDX.Vector3;
#endif

namespace SharpNav
{
	/// <summary>
	/// Do pathfinding calculations on the TiledNavMesh
	/// </summary>
	public class Utility
	{
        private static bool GetSteerTarget(
            NavMeshQuery navMeshQuery,
            Vector3 startPos,
            Vector3 endPos,
            float minTargetDist,
            Path path,
            ref Vector3 steerPos,
            ref StraightPathFlags steerPosFlag,
            ref NavPolyId steerPosRef)
        {
            StraightPath steerPath = new StraightPath();
            navMeshQuery.FindStraightPath(startPos, endPos, path, steerPath, 0);
            int nsteerPath = steerPath.Count;
            if (nsteerPath == 0)
                return false;

            //find vertex far enough to steer to
            int ns = 0;
            while (ns < nsteerPath)
            {
                if ((steerPath[ns].Flags & StraightPathFlags.OffMeshConnection) != 0 || !InRange(steerPath[ns].Point.Position, startPos, minTargetDist, 1000.0f))
                    break;

                ns++;
            }

            //failed to find good point to steer to
            if (ns >= nsteerPath)
                return false;

            steerPos = steerPath[ns].Point.Position;
            steerPos.Y = startPos.Y;
            steerPosFlag = steerPath[ns].Flags;
            if (steerPosFlag == StraightPathFlags.None && ns == (nsteerPath - 1))
                steerPosFlag = StraightPathFlags.End; // otherwise seeks path infinitely!!!
            steerPosRef = steerPath[ns].Point.Polygon;

            return true;
        }

        private static bool InRange(Vector3 v1, Vector3 v2, float r, float h)
        {
            float dx = v2.X - v1.X;
            float dy = v2.Y - v1.Y;
            float dz = v2.Z - v1.Z;
            return (dx * dx + dz * dz) < (r * r) && System.Math.Abs(dy) < h;
        }

        public static bool FindPath(
            NavMeshQuery navMeshQuery,
            NavPoint startPt,
            NavPoint endPt,
            List<Vector3> smoothPath, 
            int maxNode)
        {
            Path path = new Path();
            bool v = navMeshQuery.FindPath(
                ref startPt,
                ref endPt,
                new NavQueryFilter(),
                path);

            if (!v)
                return false;

            //find a smooth path over the mesh surface
            int npolys = path.Count;
            Vector3 iterPos = new Vector3();
            Vector3 targetPos = new Vector3();
            navMeshQuery.ClosestPointOnPoly(startPt.Polygon, startPt.Position, ref iterPos);
            navMeshQuery.ClosestPointOnPoly(path[npolys - 1], endPt.Position, ref targetPos);

            smoothPath.Add(iterPos);

            float STEP_SIZE = 0.5f;
            float SLOP = 0.01f;
            while (npolys > 0 && smoothPath.Count < maxNode)
            {
                //find location to steer towards
                Vector3 steerPos = new Vector3();
                StraightPathFlags steerPosFlag = 0;
                NavPolyId steerPosRef = NavPolyId.Null;

                if (!GetSteerTarget(navMeshQuery, iterPos, targetPos, SLOP, path, ref steerPos, ref steerPosFlag, ref steerPosRef))
                    break;

                bool endOfPath = (steerPosFlag & StraightPathFlags.End) != 0 ? true : false;
                bool offMeshConnection = (steerPosFlag & StraightPathFlags.OffMeshConnection) != 0 ? true : false;

                //find movement delta
                Vector3 delta = steerPos - iterPos;
                float len = (float)System.Math.Sqrt(Vector3.Dot(delta, delta));

                //if steer target is at end of path or off-mesh link
                //don't move past location
                if ((endOfPath || offMeshConnection) && len < STEP_SIZE)
                    len = 1;
                else
                    len = STEP_SIZE / len;

                Vector3 moveTgt = new Vector3();
                VMad(ref moveTgt, iterPos, delta, len);

                //move
                Vector3 result = new Vector3();
                List<NavPolyId> visited = new List<NavPolyId>(16);
                NavPoint startPoint = new NavPoint(path[0], iterPos);
                navMeshQuery.MoveAlongSurface(ref startPoint, ref moveTgt, out result, visited);
                path.FixupCorridor(visited);
                npolys = path.Count;
                float h = 0;
                navMeshQuery.GetPolyHeight(path[0], result, ref h);
                result.Y = h;
                iterPos = result;

                //handle end of path when close enough
                if (endOfPath && InRange(iterPos, steerPos, SLOP, 1.0f))
                {
                    //reached end of path
                    iterPos = targetPos;
                    if (smoothPath.Count < maxNode)
                    {
                        smoothPath.Add(iterPos);
                    }
                    break;
                }

                //store results
                if (smoothPath.Count < maxNode)
                {
                    smoothPath.Add(iterPos);
                }
            }

            return true;
        }

        /// <summary>
        /// Scaled vector addition
        /// </summary>
        /// <param name="dest">Result</param>
        /// <param name="v1">Vector 1</param>
        /// <param name="v2">Vector 2</param>
        /// <param name="s">Scalar</param>
        private static void VMad(ref Vector3 dest, Vector3 v1, Vector3 v2, float s)
        {
            dest.X = v1.X + v2.X * s;
            dest.Y = v1.Y + v2.Y * s;
            dest.Z = v1.Z + v2.Z * s;
        }
    }
}

#endif