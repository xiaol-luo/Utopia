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
	class MoveAgent;

	class MoveMgr
	{
	public:
		MoveMgr(Scene *scene);
		virtual ~MoveMgr();

		bool Awake();
		void Update();

	public:
		MoveAgent *GetMoveAgent(uint64_t agent_id);
		void SetMoveMaxSpeed(uint64_t agent_id, float max_speed);
		NavMesh * GetNavMesh() { return m_nav_mesh; }

		void TryMoveToPos(uint64_t agent_id, const Vector3 &pos);
		void TryMoveToDir(uint64_t agent_id, float angle);
		void CancelMove(uint64_t agent_id);
		void CancelForceMove(uint64_t agent_id);
		void ForceMoveLine(uint64_t agent_id, const Vector2 &dir, float speed, float time_sec, bool ignore_terrian);
		void ForcePos(uint64_t agent_id, const Vector3 &destination, float speed);
		void ChangeForcePosDestination(uint64_t agent_id, const Vector3 &destination);
		void Immobilized(uint64_t agent_id, long ms);
		void CancelImmobilized(uint64_t agent_id);
		void Flash(uint64_t agent_id, const Vector3 &val);

	public:
		void OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj);
		void OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj);

	protected:
		Scene *m_scene = nullptr;
		NavMesh *m_nav_mesh = nullptr;
		std::unordered_map<uint64_t, std::weak_ptr<MoveObject>> m_move_objs;
		std::unordered_map<uint64_t, MoveAgent *> m_move_agents;
		uint64_t m_last_move_agent_id = 0;
	};
}
