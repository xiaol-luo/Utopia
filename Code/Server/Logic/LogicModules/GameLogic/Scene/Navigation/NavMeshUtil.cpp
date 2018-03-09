#include "NavMeshUtil.h"
#include "DetourTileCache.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourTileCacheBuilder.h"
#include <string>
#include "InputGeom.h"
#include "DetourCommon.h"


struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

void saveNavMesh(const char* path, const dtNavMesh* mesh)
{
	if (!mesh) return;

	FILE* fp = fopen(path, "wb");
	if (!fp)
		return;

	// Store header.
	NavMeshSetHeader header;
	header.magic = NAVMESHSET_MAGIC;
	header.version = NAVMESHSET_VERSION;
	header.numTiles = 0;
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;
		header.numTiles++;
	}
	memcpy(&header.params, mesh->getParams(), sizeof(dtNavMeshParams));
	fwrite(&header, sizeof(NavMeshSetHeader), 1, fp);

	// Store tiles.
	for (int i = 0; i < mesh->getMaxTiles(); ++i)
	{
		const dtMeshTile* tile = mesh->getTile(i);
		if (!tile || !tile->header || !tile->dataSize) continue;

		NavMeshTileHeader tileHeader;
		tileHeader.tileRef = mesh->getTileRef(tile);
		tileHeader.dataSize = tile->dataSize;
		fwrite(&tileHeader, sizeof(tileHeader), 1, fp);

		fwrite(tile->data, tile->dataSize, 1, fp);
	}

	fclose(fp);
}

dtNavMesh* LoadNavMesh(const char* path)
{
	FILE* fp = fopen(path, "rb");
	if (!fp) return 0;

	// Read header.
	NavMeshSetHeader header;
	size_t readLen = fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (readLen != 1)
	{
		fclose(fp);
		return 0;
	}
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		return 0;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		return 0;
	}

	dtNavMesh* mesh = dtAllocNavMesh();
	if (!mesh)
	{
		fclose(fp);
		return 0;
	}
	dtStatus status = mesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		return 0;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		readLen = fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (readLen != 1)
		{
			fclose(fp);
			return 0;
		}

		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		readLen = fread(data, tileHeader.dataSize, 1, fp);
		if (readLen != 1)
		{
			fclose(fp);
			return 0;
		}

		mesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	return mesh;
}



int FastLZCompressor::maxCompressedSize(const int bufferSize)
{
	return (int)(bufferSize* 1.05f);
}

dtStatus FastLZCompressor::compress(const unsigned char* buffer, const int bufferSize,
	unsigned char* compressed, const int /*maxCompressedSize*/, int* compressedSize)
{
	// *compressedSize = fastlz_compress((const void *const)buffer, bufferSize, compressed);
	memcpy(compressed, buffer, bufferSize);
	*compressedSize = bufferSize;
	return DT_SUCCESS;
}

dtStatus FastLZCompressor::decompress(const unsigned char* compressed, const int compressedSize,
	unsigned char* buffer, const int maxBufferSize, int* bufferSize)
{
	// *bufferSize = fastlz_decompress(compressed, compressedSize, buffer, maxBufferSize);
	memcpy(buffer, compressed, compressedSize);
	*bufferSize = compressedSize;
	return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
}

LinearAllocator::LinearAllocator(const size_t cap) : buffer(0), capacity(0), top(0), high(0)
{
	resize(cap);
}

LinearAllocator::~LinearAllocator()
{
	dtFree(buffer);
}

void LinearAllocator::resize(const size_t cap)
{
	if (buffer) dtFree(buffer);
	buffer = (unsigned char*)dtAlloc(cap, DT_ALLOC_PERM);
	capacity = cap;
}

void LinearAllocator::reset()
{
	high = dtMax(high, top);
	top = 0;
}

void* LinearAllocator::alloc(const size_t size)
{
	if (!buffer)
		return 0;
	if (top + size > capacity)
		return 0;
	unsigned char* mem = &buffer[top];
	top += size;
	return mem;
}

void LinearAllocator::free(void* /*ptr*/)
{
	// Empty
}

MeshProcess::MeshProcess() : m_geom(0)
{
}

void MeshProcess::init(InputGeom* geom)
{
	m_geom = geom;
}

void MeshProcess::process(struct dtNavMeshCreateParams* params,
	unsigned char* polyAreas, unsigned short* polyFlags)
{
	// Update poly flags from areas.
	for (int i = 0; i < params->polyCount; ++i)
	{
		if (polyAreas[i] == DT_TILECACHE_WALKABLE_AREA)
			polyAreas[i] = SAMPLE_POLYAREA_GROUND;

		if (polyAreas[i] == SAMPLE_POLYAREA_GROUND ||
			polyAreas[i] == SAMPLE_POLYAREA_GRASS ||
			polyAreas[i] == SAMPLE_POLYAREA_ROAD)
		{
			polyFlags[i] = SAMPLE_POLYFLAGS_WALK;
		}
		else if (polyAreas[i] == SAMPLE_POLYAREA_WATER)
		{
			polyFlags[i] = SAMPLE_POLYFLAGS_SWIM;
		}
		else if (polyAreas[i] == SAMPLE_POLYAREA_DOOR)
		{
			polyFlags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
		}
	}

	// Pass in off-mesh connections.
	if (m_geom)
	{
		params->offMeshConVerts = m_geom->getOffMeshConnectionVerts();
		params->offMeshConRad = m_geom->getOffMeshConnectionRads();
		params->offMeshConDir = m_geom->getOffMeshConnectionDirs();
		params->offMeshConAreas = m_geom->getOffMeshConnectionAreas();
		params->offMeshConFlags = m_geom->getOffMeshConnectionFlags();
		params->offMeshConUserID = m_geom->getOffMeshConnectionId();
		params->offMeshConCount = m_geom->getOffMeshConnectionCount();
	}
}