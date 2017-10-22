#pragma once
#include "SceneObject.h"
#include "GameLogic/Scene/Defines/SceneObjectDefine.h"
#include <memory>

namespace GameLogic
{
	class NavAgent;
	class MoveAgent;

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
		MoveAgent *m_move_agent = nullptr;

	public:
		void SetMoveAgent(MoveAgent *val) { m_move_agent = val; }
		MoveAgent * GetMoveAgent() { return m_move_agent; }
		const Vector3 & GetVelocity();
		EMoveAgentState GetMoveAgentState();
		void TryMoveToPos(const Vector3 &pos);
		void TryMoveToDir(float angle);
		void CancelMove();
		void CancelForceMove();
		void ForceMoveLine(const Vector2 &dir, float speed, float time_sec, bool ignore_terrian);
		void ForcePos(const Vector3 &destination, float speed);
		void ChangeForcePosDestination(const Vector3 &destination);
		void Immobilized(long ms);
		void CancelImmobilized();
		void Flash(const Vector3 &val);

	public:
		static void OnMoveStateChange(std::weak_ptr<MoveObject> obj, MoveAgent *agent, EMoveAgentState old_state);
		static void OnPostChange(std::weak_ptr<MoveObject> obj, MoveAgent *agent, Vector3 old_pos);
		static void OnVelocityChange(std::weak_ptr<MoveObject> obj, MoveAgent *agent, Vector3 old_velocity);
	};
}