#include "NavMesh.h"
#include "DetourTileCache.h"
#include "DetourNavMesh.h"
#include "InputGeom.h"
#include "Recast.h"
#include "NavMeshUtil.h"
#include "DetourCommon.h"
#include "DetourCrowd.h"
#include "DetourNavMeshQuery.h"
#include <assert.h>

extern dtNavMesh* LoadNavMesh(const char* path);
static const int EXPECTED_LAYERS_PER_TILE = 4;
static const int MAX_LAYERS = 32;
static const int DEFAULT_TILE_SIZE = 48;

struct TileCacheData
{
	unsigned char* data;
	int dataSize;
};

struct RasterizationContext
{
	RasterizationContext() :
		solid(0),
		triareas(0),
		lset(0),
		chf(0),
		ntiles(0)
	{
		memset(tiles, 0, sizeof(TileCacheData)*MAX_LAYERS);
	}

	~RasterizationContext()
	{
		rcFreeHeightField(solid);
		delete[] triareas;
		rcFreeHeightfieldLayerSet(lset);
		rcFreeCompactHeightfield(chf);
		for (int i = 0; i < MAX_LAYERS; ++i)
		{
			dtFree(tiles[i].data);
			tiles[i].data = 0;
		}
	}

	rcHeightfield* solid;
	unsigned char* triareas;
	rcHeightfieldLayerSet* lset;
	rcCompactHeightfield* chf;
	TileCacheData tiles[MAX_LAYERS];
	int ntiles;
};


namespace GameLogic
{
	NavMesh::NavMesh()
	{
		m_rcCtx = new rcContext;
		m_talloc = new LinearAllocator(32000);
		m_tcomp = new FastLZCompressor();
		m_tmproc = new MeshProcess();
		m_dtCrowd = dtAllocCrowd();
		m_dtNavMeshQuery = dtAllocNavMeshQuery();
	}

	NavMesh::~NavMesh()
	{
		delete m_talloc; m_tmproc = nullptr;
		delete m_tcomp; m_tcomp = nullptr;
		delete m_tmproc; m_tmproc = nullptr;
		dtFreeCrowd(m_dtCrowd); m_dtCrowd = nullptr;
		dtFreeNavMeshQuery(m_dtNavMeshQuery); m_dtNavMeshQuery = nullptr;
		this->Reset();
	}

	void NavMesh::Reset()
	{
		if (nullptr != m_dtNavMesh)
			dtFreeNavMesh(m_dtNavMesh);
		if (nullptr != m_dtTileCache)
			dtFreeTileCache(m_dtTileCache);
		if (nullptr != m_geom)
			delete m_geom;
		m_dtTileCache = nullptr;
		m_dtNavMesh = nullptr;
		m_geom = nullptr;
	}

	void NavMesh::UpdateTerrian()
	{
		if (nullptr != m_dtTileCache && nullptr != m_dtNavMesh)
		{
			bool is_finished = false;
			int try_times = 0;
			while (!is_finished && try_times++ < 10000)
			{
				m_dtTileCache->update(0, m_dtNavMesh, &is_finished);
			}
		}
	}

	bool NavMesh::LoadTerrain(std::string file_path)
	{
		this->Reset();
		bool ret = true;
		do
		{
			m_geom = new InputGeom;
			if (!m_geom->load(m_rcCtx, file_path))
			{
				ret = false;
				break;
			}

			m_tmproc->init(m_geom);

			// handle setting
			const BuildSettings *b_setting = m_geom->getBuildSettings();
			int tile_size = b_setting->tileSize;
			if (tile_size <= 0) tile_size = DEFAULT_TILE_SIZE;
			const float* bmin = m_geom->getNavMeshBoundsMin();
			const float* bmax = m_geom->getNavMeshBoundsMax();
			int gw = 0, gh = 0;
			rcCalcGridSize(bmin, bmax, b_setting->cellSize, &gw, &gh);
			const int ts = (int)tile_size;
			const int tw = (gw + ts - 1) / ts;
			const int th = (gh + ts - 1) / ts;
			int tileBits = rcMin((int)dtIlog2(dtNextPow2(tw*th*EXPECTED_LAYERS_PER_TILE)), 14);
			if (tileBits > 14) tileBits = 14;
			int polyBits = 22 - tileBits;
			int maxTiles = 1 << tileBits;
			int maxPolysPerTile = 1 << polyBits;
			
			// Generation params.
			rcConfig cfg;
			memset(&cfg, 0, sizeof(cfg));
			cfg.cs = b_setting->cellSize;
			cfg.ch = b_setting->cellHeight;
			cfg.walkableSlopeAngle = b_setting->agentMaxSlope;
			cfg.walkableHeight = (int)ceilf(b_setting->agentHeight / cfg.ch);
			cfg.walkableClimb = (int)floorf(b_setting->agentMaxClimb / cfg.ch);
			cfg.walkableRadius = (int)ceilf(b_setting->agentRadius / cfg.cs);
			cfg.maxEdgeLen = (int)(b_setting->edgeMaxLen / b_setting->cellSize);
			cfg.maxSimplificationError = b_setting->edgeMaxError;
			cfg.minRegionArea = (int)rcSqr(b_setting->regionMinSize);		// Note: area = size*size
			cfg.mergeRegionArea = (int)rcSqr(b_setting->regionMergeSize);	// Note: area = size*size
			cfg.maxVertsPerPoly = (int)b_setting->vertsPerPoly;;
			cfg.tileSize = (int)tile_size;
			cfg.borderSize = cfg.walkableRadius + 3; // Reserve enough padding.
			cfg.width = cfg.tileSize + cfg.borderSize * 2;
			cfg.height = cfg.tileSize + cfg.borderSize * 2;
			cfg.detailSampleDist = b_setting->detailSampleDist < 0.9f ? 0 : b_setting->cellSize * b_setting->detailSampleDist;
			cfg.detailSampleMaxError = b_setting->cellHeight * b_setting->detailSampleMaxError;
			rcVcopy(cfg.bmin, bmin);
			rcVcopy(cfg.bmax, bmax);
			
			m_area.lt = Vector3(cfg.bmin).XZ();
			m_area.rb = Vector3(cfg.bmax).XZ();

			// Tile cache params.
			dtTileCacheParams tcparams;
			memset(&tcparams, 0, sizeof(tcparams));
			rcVcopy(tcparams.orig, bmin);
			tcparams.cs = b_setting->cellSize;
			tcparams.ch = b_setting->cellHeight;
			tcparams.width = (int)tile_size;
			tcparams.height = (int)tile_size;
			tcparams.walkableHeight = b_setting->agentHeight;
			tcparams.walkableRadius = b_setting->agentRadius;
			tcparams.walkableClimb = b_setting->agentMaxClimb;
			tcparams.maxSimplificationError = b_setting->edgeMaxError;
			tcparams.maxTiles = tw*th*EXPECTED_LAYERS_PER_TILE;
			tcparams.maxObstacles = 128;

			dtFreeTileCache(m_dtTileCache);
			m_dtTileCache = dtAllocTileCache();
			if (!m_dtTileCache)
			{
				m_rcCtx->log(RC_LOG_ERROR, "buildTiledNavigation: Could not allocate tile cache.");
				ret = false;
				break;
			}
			dtStatus status = m_dtTileCache->init(&tcparams, m_talloc, m_tcomp, m_tmproc);
			if (dtStatusFailed(status))
			{
				m_rcCtx->log(RC_LOG_ERROR, "buildTiledNavigation: Could not init tile cache.");
				ret = false;
				break;
			}

			dtFreeNavMesh(m_dtNavMesh);
			m_dtNavMesh = dtAllocNavMesh();
			if (!m_dtNavMesh)
			{
				m_rcCtx->log(RC_LOG_ERROR, "buildTiledNavigation: Could not allocate navmesh.");
				ret = false;
				break;
			}

			dtNavMeshParams params;
			memset(&params, 0, sizeof(params));
			rcVcopy(params.orig, bmin);
			params.tileWidth = tile_size * b_setting->cellSize;
			params.tileHeight = tile_size * b_setting->cellSize;
			params.maxTiles = maxTiles;
			params.maxPolys = maxPolysPerTile;
			status = m_dtNavMesh->init(&params);
			if (dtStatusFailed(status))
			{
				m_rcCtx->log(RC_LOG_ERROR, "buildTiledNavigation: Could not init navmesh.");
				ret = false;
				break;
			}

			m_rcCtx->resetTimers();
			for (int y = 0; y < th; ++y)
			{
				for (int x = 0; x < tw; ++x)
				{
					TileCacheData tiles[MAX_LAYERS];
					memset(tiles, 0, sizeof(tiles));
					int ntiles = rasterizeTileLayers(x, y, cfg, tiles, MAX_LAYERS);

					for (int i = 0; i < ntiles; ++i)
					{
						TileCacheData* tile = &tiles[i];
						status = m_dtTileCache->addTile(tile->data, tile->dataSize, DT_COMPRESSEDTILE_FREE_DATA, 0);
						if (dtStatusFailed(status))
						{
							dtFree(tile->data);
							tile->data = 0;
							continue;
						}
					}
				}
			}

			// Build initial meshes
			m_rcCtx->startTimer(RC_TIMER_TOTAL);
			for (int y = 0; y < th; ++y)
				for (int x = 0; x < tw; ++x)
					m_dtTileCache->buildNavMeshTilesAt(x, y, m_dtNavMesh);
			m_rcCtx->stopTimer(RC_TIMER_TOTAL);

			float cacheBuildTimeMs = m_rcCtx->getAccumulatedTime(RC_TIMER_TOTAL) / 1000.0f;
			size_t cacheBuildMemUsage = m_talloc->high;

			const dtNavMesh* nav = m_dtNavMesh;
			int navmeshMemUsage = 0;
			for (int i = 0; i < nav->getMaxTiles(); ++i)
			{
				const dtMeshTile* tile = nav->getTile(i);
				if (tile->header)
					navmeshMemUsage += tile->dataSize;
			}

			printf("cacheBuildTimeMs = %.1f ms \n", cacheBuildTimeMs);
			printf("cacheBuildMemUsage = %.1f kB \n", cacheBuildMemUsage / 1024.0f);
			printf("navmeshMemUsage = %.1f kB \n", navmeshMemUsage / 1024.0f);

			{
				// navmesh query
				status = m_dtNavMeshQuery->init(m_dtNavMesh, 512);
				if (dtStatusFailed(status))
				{
					ret = false;
					m_rcCtx->log(RC_LOG_ERROR, "buildTiledNavigation: Could not allocate navmesh.");
					break;
				}
			}
			{
				// dtcrow
				m_dtCrowd->init(512, 2.5, m_dtNavMesh);

				// Make polygons with 'disabled' flag invalid.
				m_dtCrowd->getEditableFilter(0)->setExcludeFlags(SAMPLE_POLYFLAGS_DISABLED);
				// Setup local avoidance params to different qualities.
				dtObstacleAvoidanceParams params;
				// Use mostly default settings, copy from dtCrowd.
				memcpy(&params, m_dtCrowd->getObstacleAvoidanceParams(0), sizeof(dtObstacleAvoidanceParams));
				// Low (11)
				params.velBias = 0.5f;
				params.adaptiveDivs = 5;
				params.adaptiveRings = 2;
				params.adaptiveDepth = 1;
				m_dtCrowd->setObstacleAvoidanceParams(0, &params);
				// Medium (22)
				params.velBias = 0.5f;
				params.adaptiveDivs = 5;
				params.adaptiveRings = 2;
				params.adaptiveDepth = 2;
				m_dtCrowd->setObstacleAvoidanceParams(1, &params);
				// Good (45)
				params.velBias = 0.5f;
				params.adaptiveDivs = 7;
				params.adaptiveRings = 2;
				params.adaptiveDepth = 3;
				m_dtCrowd->setObstacleAvoidanceParams(2, &params);
				// High (66)
				params.velBias = 0.5f;
				params.adaptiveDivs = 7;
				params.adaptiveRings = 3;
				params.adaptiveDepth = 3;
				m_dtCrowd->setObstacleAvoidanceParams(3, &params);
			}
		} while (false);

		if (!ret)
			this->Reset();
		return ret;
	}

	bool NavMesh::FindNearestPoint(const Vector3 &center, dtPolyRef &target_ref, Vector3 &target_pos)
	{
		const float *ext = m_dtCrowd->getQueryExtents();
		return this->FindNearestPoint(center, Vector3(ext), target_ref, target_pos);
	}

	bool NavMesh::FindNearestPoint(const Vector3 &center, const Vector3 range, dtPolyRef &target_ref, Vector3 &target_pos)
	{
		const dtNavMeshQuery *navquery = m_dtCrowd->getNavMeshQuery();
		float out_pos[3]; memset(out_pos, 0, sizeof(out_pos));
		dtStatus state = navquery->findNearestPoly(center.toPointer(), range.toPointer(), DefaultFilter(), &target_ref, out_pos);
		if (dtStatusSucceed(state) && 0 != target_ref)
		{
			target_pos = Vector3(out_pos);
			return true;
		}
		return false;
	}

	bool NavMesh::Raycast(const Vector3 &start_pos, const Vector3 &end_pos, Vector3 &hit_pos)
	{
		dtPolyRef start_poly_ref = 0; Vector3 tmp_pos;
		if (this->FindNearestPoint(start_pos, Vector3(0.1f, 1.0f, 0.1f), start_poly_ref, tmp_pos))
		{
			dtRaycastHit hit; memset(&hit, 0, sizeof(hit));
			dtStatus state = m_dtNavMeshQuery->raycast(start_poly_ref, tmp_pos.toPointer(),
				end_pos.toPointer(), DefaultFilter(), DT_RAYCAST_USE_COSTS, &hit);
			if (dtStatusSucceed(state))
			{
				if (hit.t >= 0 && hit.t < 1)
					hit_pos = tmp_pos + (end_pos - tmp_pos) * hit.t;
				else if (hit.t >= 1)
					hit_pos = end_pos;
				return true;
			}
		}
		return false;
	}

	bool NavMesh::GetPolyRef(const Vector3 &pos, dtPolyRef &out_ref)
	{
		dtPolyRef ref = 0; int ref_count = 0;
		dtStatus status = m_dtNavMeshQuery->queryPolygons(
			pos.toPointer(), Vector3(0.1f, 1.0f, 0.1f).toPointer(), DefaultFilter(), &ref, &ref_count, 1);
		if (dtStatusSucceed(status) && ref_count > 0)
		{
			out_ref = ref;
			return true;
		}
		return false;
	}

	int NavMesh::rasterizeTileLayers(const int tx, const int ty, const rcConfig& cfg, TileCacheData* tiles, const int maxTiles)
	{
		if (!m_geom || !m_geom->getMesh() || !m_geom->getChunkyMesh())
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildTile: Input mesh is not specified.");
			return 0;
		}

		FastLZCompressor comp;
		RasterizationContext rc;

		const float* verts = m_geom->getMesh()->getVerts();
		const int nverts = m_geom->getMesh()->getVertCount();
		const rcChunkyTriMesh* chunkyMesh = m_geom->getChunkyMesh();

		// Tile bounds.
		const float tcs = cfg.tileSize * cfg.cs;

		rcConfig tcfg;
		memcpy(&tcfg, &cfg, sizeof(tcfg));

		tcfg.bmin[0] = cfg.bmin[0] + tx*tcs;
		tcfg.bmin[1] = cfg.bmin[1];
		tcfg.bmin[2] = cfg.bmin[2] + ty*tcs;
		tcfg.bmax[0] = cfg.bmin[0] + (tx + 1)*tcs;
		tcfg.bmax[1] = cfg.bmax[1];
		tcfg.bmax[2] = cfg.bmin[2] + (ty + 1)*tcs;
		tcfg.bmin[0] -= tcfg.borderSize*tcfg.cs;
		tcfg.bmin[2] -= tcfg.borderSize*tcfg.cs;
		tcfg.bmax[0] += tcfg.borderSize*tcfg.cs;
		tcfg.bmax[2] += tcfg.borderSize*tcfg.cs;

		// Allocate voxel heightfield where we rasterize our input data to.
		rc.solid = rcAllocHeightfield();
		if (!rc.solid)
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
			return 0;
		}
		if (!rcCreateHeightfield(m_rcCtx, *rc.solid, tcfg.width, tcfg.height, tcfg.bmin, tcfg.bmax, tcfg.cs, tcfg.ch))
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
			return 0;
		}

		// Allocate array that can hold triangle flags.
		// If you have multiple meshes you need to process, allocate
		// and array which can hold the max number of triangles you need to process.
		rc.triareas = new unsigned char[chunkyMesh->maxTrisPerChunk];
		if (!rc.triareas)
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", chunkyMesh->maxTrisPerChunk);
			return 0;
		}

		float tbmin[2], tbmax[2];
		tbmin[0] = tcfg.bmin[0];
		tbmin[1] = tcfg.bmin[2];
		tbmax[0] = tcfg.bmax[0];
		tbmax[1] = tcfg.bmax[2];
		int cid[512];// TODO: Make grow when returning too many items.
		const int ncid = rcGetChunksOverlappingRect(chunkyMesh, tbmin, tbmax, cid, 512);
		if (!ncid)
		{
			return 0; // empty
		}

		for (int i = 0; i < ncid; ++i)
		{
			const rcChunkyTriMeshNode& node = chunkyMesh->nodes[cid[i]];
			const int* tris = &chunkyMesh->tris[node.i * 3];
			const int ntris = node.n;

			memset(rc.triareas, 0, ntris * sizeof(unsigned char));
			rcMarkWalkableTriangles(m_rcCtx, tcfg.walkableSlopeAngle,
				verts, nverts, tris, ntris, rc.triareas);

			if (!rcRasterizeTriangles(m_rcCtx, verts, nverts, tris, rc.triareas, ntris, *rc.solid, tcfg.walkableClimb))
				return 0;
		}

		// Once all geometry is rasterized, we do initial pass of filtering to
		// remove unwanted overhangs caused by the conservative rasterization
		// as well as filter spans where the character cannot possibly stand.
		rcFilterLowHangingWalkableObstacles(m_rcCtx, tcfg.walkableClimb, *rc.solid);
		rcFilterLedgeSpans(m_rcCtx, tcfg.walkableHeight, tcfg.walkableClimb, *rc.solid);
		rcFilterWalkableLowHeightSpans(m_rcCtx, tcfg.walkableHeight, *rc.solid);

		rc.chf = rcAllocCompactHeightfield();
		if (!rc.chf)
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
			return 0;
		}
		if (!rcBuildCompactHeightfield(m_rcCtx, tcfg.walkableHeight, tcfg.walkableClimb, *rc.solid, *rc.chf))
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
			return 0;
		}

		// Erode the walkable area by agent radius.
		if (!rcErodeWalkableArea(m_rcCtx, tcfg.walkableRadius, *rc.chf))
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
			return 0;
		}

		// (Optional) Mark areas.
		const ConvexVolume* vols = m_geom->getConvexVolumes();
		for (int i = 0; i < m_geom->getConvexVolumeCount(); ++i)
		{
			rcMarkConvexPolyArea(m_rcCtx, vols[i].verts, vols[i].nverts,
				vols[i].hmin, vols[i].hmax,
				(unsigned char)vols[i].area, *rc.chf);
		}

		rc.lset = rcAllocHeightfieldLayerSet();
		if (!rc.lset)
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'lset'.");
			return 0;
		}
		if (!rcBuildHeightfieldLayers(m_rcCtx, *rc.chf, tcfg.borderSize, tcfg.walkableHeight, *rc.lset))
		{
			m_rcCtx->log(RC_LOG_ERROR, "buildNavigation: Could not build heighfield layers.");
			return 0;
		}

		rc.ntiles = 0;
		for (int i = 0; i < rcMin(rc.lset->nlayers, MAX_LAYERS); ++i)
		{
			TileCacheData* tile = &rc.tiles[rc.ntiles++];
			const rcHeightfieldLayer* layer = &rc.lset->layers[i];

			// Store header
			dtTileCacheLayerHeader header;
			header.magic = DT_TILECACHE_MAGIC;
			header.version = DT_TILECACHE_VERSION;

			// Tile layer location in the navmesh.
			header.tx = tx;
			header.ty = ty;
			header.tlayer = i;
			dtVcopy(header.bmin, layer->bmin);
			dtVcopy(header.bmax, layer->bmax);

			// Tile info.
			header.width = (unsigned char)layer->width;
			header.height = (unsigned char)layer->height;
			header.minx = (unsigned char)layer->minx;
			header.maxx = (unsigned char)layer->maxx;
			header.miny = (unsigned char)layer->miny;
			header.maxy = (unsigned char)layer->maxy;
			header.hmin = (unsigned short)layer->hmin;
			header.hmax = (unsigned short)layer->hmax;

			dtStatus status = dtBuildTileCacheLayer(&comp, &header, layer->heights, layer->areas, layer->cons,
				&tile->data, &tile->dataSize);
			if (dtStatusFailed(status))
			{
				return 0;
			}
		}

		// Transfer ownsership of tile data from build context to the caller.
		int n = 0;
		for (int i = 0; i < rcMin(rc.ntiles, maxTiles); ++i)
		{
			tiles[n++] = rc.tiles[i];
			rc.tiles[i].data = 0;
			rc.tiles[i].dataSize = 0;
		}

		return n;
	}
	const dtQueryFilter * NavMesh::DefaultFilter()
	{
		return m_dtCrowd->getFilter(0);
	}
}

