#include "DetourCrowd.h"

class dtCrowd;
class dtNavMeshQuery;

namespace GameLogic
{
	class Scene;
	class NavMesh;

	class NavMgr
	{
	public: 
		NavMgr();
		virtual ~NavMgr();
		bool Init(NavMesh *navMesh);
		void Update();

	protected:
		dtCrowd *m_dtCrowd = nullptr;
		dtNavMeshQuery *m_dtNavMeshQuery = nullptr;
	};
}