#pragma once
#include "SceneObject.h"
#include "GameLogic/Scene/Defines/SceneObjectDefine.h"

namespace NetProto
{
	class MoveObjectMutableState;
	class MoveObjectState;
}

namespace GameLogic
{
	class NavAgent;
	class MoveAgent;

	class MoveObject : public SceneObject
	{
	public:
		MoveObject(ESceneObjectType obj_type);
		virtual ~MoveObject() override;

	public:
		virtual void OnEnterScene(Scene *scene) override;
		virtual void OnLeaveScene(Scene *scene) override;
		virtual void Update(long long now_ms) override;

	public:
		void SetBodyHeight(float height) { m_body_height = height; }
		float GetBodyHeight() const { return m_body_height; }
		void SetSpeed(float speed);
		float GetSpeed() const { return m_speed; }

	protected:
		float m_speed = 6.0f;
		float m_body_height = 2.0f;
		MoveAgent *m_move_agent = nullptr;
		void OnSpeedChange(float old_val);
		void OnRadiusChange(float old_val);

	public:
		void SetMoveAgent(MoveAgent *val) { m_move_agent = val; }
		MoveAgent * GetMoveAgent() { return m_move_agent; }
		const Vector3 & GetVelocity();
		NetProto::EMoveAgentState GetMoveAgentState();
		NetProto::EMoveState GetMoveState();
		virtual std::vector<SyncClientMsg> ColllectSyncClientMsg(int filter_type, bool include_unchanged) override;
	protected:
		NetProto::MoveObjectState * GetPbMoveObjectState();
		NetProto::MoveObjectMutableState * GetPbMoveObjectMutableState();

	protected:
		void OnMoveAgentStateChange(NetProto::EMoveAgentState old_val);
		void OnVelocityChange(const Vector3 &old_val);
		virtual void OnPosChange(const Vector3 &old_val) override;

	public:
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
		static void MoveStateChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent *agent, NetProto::EMoveAgentState old_state);
		static void PosChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent *agent, Vector3 old_pos);
		static void VelocityChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent *agent, Vector3 old_velocity);
	};
}