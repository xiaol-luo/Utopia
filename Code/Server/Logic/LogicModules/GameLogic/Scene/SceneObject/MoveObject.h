#pragma once
#include "SceneObject.h"
#include "GameLogic/Scene/Defines/SceneObjectDefine.h"

namespace GameLogic
{
	class NavAgent;

	class MoveObject : public SceneObject
	{
	public:
		MoveObject(ESceneObjectType obj_type);
		virtual ~MoveObject();

	public:
		virtual void OnEnterScene(Scene *scene);
		virtual void OnLeaveScene(Scene *scene);
		virtual void Update(long long now_ms);

	public:
		void SetRadius(float radius) { m_radius = radius; }
		float GetRadius() const { return m_radius; }
		void SetHeight(float height) { m_height = height; }
		float GetHeight() const { return m_height; }
		void SetSpeed(float speed);
		float GetSpeed() const { return m_speed; }
		void SetMass(float mass) { m_mass = mass; }
		float GetMass() const { return m_mass; }

	protected:
		float m_speed = 6.0f;
		float m_radius = 0.4f;
		float m_height = 2.0f;
		float m_mass = 100.0f;
		uint64_t m_nav_agent_id = 0;

	public:
		uint64_t GetNavAgentId() { return m_nav_agent_id; }
		void SetNavAgentId(uint64_t val) { m_nav_agent_id = val; }
		void SetVelocity(Vector3 val);
		const Vector3 & GetVelocity() { return m_velocity; }
		void TryMoveToPos(const Vector3 &pos);
		void TryMoveToDir(float angle);
		void TryStopMove();
		EMoveType GetMoveType();
		Vector3 GetDesiredMovePos();
		Vector3 GetForceMovePos();

	protected:
		Vector3 m_velocity;
	};
}