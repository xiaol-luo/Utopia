#pragma once

#include <memory>
#include <unordered_map>
#include <stdint.h>
#include <Common/Math/Vector3.h>

namespace GameLogic
{
	class MoveObject;
	class NavMesh;
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
		void TryMoveToPos(uint64_t agent_id, const Vector3 &pos);
		void TryMoveToDir(uint64_t agent_id, float angle);
		void StopMove(uint64_t agent_id);
		void TryResumeMove(uint64_t agent_id);
		NavAgent * GetNavAgent(uint64_t agent_id);
		void SetMaxSpeed(uint64_t agent_id, float max_speed);

	public:
		void OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj);
		void OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj);
		void OnNavAgentMoved(NavAgent *agent, std::weak_ptr<MoveObject> weak_move_obj);

	protected:
		Scene *m_scene = nullptr;
		NavMesh *m_nav_mesh = nullptr;
		std::unordered_map<uint64_t, std::weak_ptr<MoveObject>> m_move_objs;
		std::unordered_map<uint64_t, NavAgent *> m_nav_agents;
		uint64_t m_last_nav_agent_id = 0;
	};
}
