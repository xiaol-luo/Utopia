#pragma once

#include <string>
#include "Recast.h"

class dtNavMesh;
class dtTileCache;
class InputGeom;
class rcContext;
struct LinearAllocator;
struct FastLZCompressor;
struct MeshProcess;
struct TileCacheData;
class dtCrowd;
class dtNavMeshQuery;

#include "DetourNavMesh.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/GeometryDefine.h"
#include "DetourNavMeshQuery.h"
#include <string.h>

namespace GameLogic
{
	class Scene;

	class NavMesh
	{
	public:
		NavMesh();
		virtual ~NavMesh();

		void UpdateTerrian();
		bool LoadTerrain(std::string file_path);
		dtCrowd * GetCrowd() { return m_dtCrowd; }
		dtNavMeshQuery * GetNavMeshQuery() { return m_dtNavMeshQuery; }

		bool FindNearestPoint(const Vector3 &center, dtPolyRef &target_ref, Vector3 &target_pos);
		bool FindNearestPoint(const Vector3 &center, const Vector3 range, dtPolyRef &target_ref, Vector3 &target_pos);
		bool Raycast(const Vector3 &start_pos, const Vector3 &end_pos, Vector3 &hit_pos);
		bool GetPolyRef(const Vector3 &pos, dtPolyRef &out_ref);
		AABB2 GetArea() { return m_area; }

	protected:
		rcContext *m_rcCtx = nullptr;
		LinearAllocator *m_talloc;
		FastLZCompressor *m_tcomp;
		MeshProcess *m_tmproc;
		InputGeom *m_geom = nullptr;
		dtNavMesh *m_dtNavMesh = nullptr;
		dtTileCache *m_dtTileCache = nullptr;
		dtCrowd *m_dtCrowd = nullptr;
		dtNavMeshQuery *m_dtNavMeshQuery = nullptr;
		void Reset();
		int rasterizeTileLayers(const int tx, const int ty, 
			const rcConfig& cfg, TileCacheData* tiles, const int maxTiles);
		const dtQueryFilter * DefaultFilter();

		AABB2 m_area;
	};
}