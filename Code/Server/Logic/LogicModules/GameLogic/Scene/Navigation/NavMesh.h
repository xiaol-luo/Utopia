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
#include "Common/Math/Vector3.h"

namespace GameLogic
{
	class Scene;

	class NavMesh
	{
	public:
		NavMesh(Scene *scene);
		virtual ~NavMesh();

		void UpdateTerrian();
		bool LoadTerrain(std::string file_path);
		dtCrowd * GetCrowd() { return m_dtCrowd; }
		dtNavMeshQuery * GetNavMeshQuery() { return m_dtNavMeshQuery; }

		void FindNearestPoint(const Vector3 & pos, int filter, dtPolyRef * target_ref, Vector3 *target_pos);
		Vector3 Raycast(const Vector3 &start_pos, const Vector3 &endPos);

	protected:
		Scene *m_scene = nullptr;
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
		int NavMesh::rasterizeTileLayers(const int tx, const int ty, 
			const rcConfig& cfg, TileCacheData* tiles, const int maxTiles);
	};
}