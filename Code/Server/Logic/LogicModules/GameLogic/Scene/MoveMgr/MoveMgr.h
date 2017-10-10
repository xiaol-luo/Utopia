#include <memory>
#include <unordered_map>

namespace GameLogic
{
	class MoveObject;
	class NavMgr;
	class Scene;
	class NavAgent;

	class MoveMgr
	{
	public:
		MoveMgr(Scene *scene);
		virtual ~MoveMgr();

		bool Awake();
		void Update();

	public:
		void OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj);
		void OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj);

	protected:
		Scene *m_scene = nullptr;
		NavMgr *m_navMgr = nullptr;
		std::unordered_map<uint64_t, std::weak_ptr<MoveObject>> m_move_objs;
		std::unordered_map<uint64_t, NavAgent *> m_nav_agents;

		uint64_t m_last_nav_agent_id = 0;
	};
}
