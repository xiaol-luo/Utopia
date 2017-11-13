#include "MoveObject.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/MoveMgr/MoveMgr.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "Common/Geometry/GeometryUtils.h"
#include "GameLogic/Scene/EventDispacher/EventDispacher.h"

namespace GameLogic
{
	MoveObject::MoveObject(ESceneObjectType obj_type) : SceneObject(obj_type)
	{

	}

	MoveObject::~MoveObject()
	{

	}

	void MoveObject::OnEnterScene(Scene * scene)
	{
		SceneObject::OnLeaveScene(scene);
	}

	void MoveObject::OnLeaveScene(Scene * scene)
	{
		SceneObject::OnLeaveScene(scene);
	}

	void MoveObject::Update(long long now_ms)
	{
		SceneObject::Update(now_ms);
	}

	void MoveObject::SetSpeed(float speed)
	{
		if (abs(m_speed - speed) < FLT_EPSILON)
			return;

		float old_val = m_speed;
		m_speed = speed;
		if (nullptr != m_move_agent)
			m_move_agent->SetNavMaxSpeed(m_speed);
		this->OnSpeedChange(old_val);
	}

	void MoveObject::OnSpeedChange(float old_val)
	{

	}

	void MoveObject::OnRadiusChange(float old_val)
	{

	}

	const Vector3 & MoveObject::GetVelocity()
	{
		if (m_move_agent)
			return m_move_agent->GetVelocity();
		return Vector3::zero;
	}

	void MoveObject::OnMoveAgentStateChange(NetProto::EMoveAgentState old_val)
	{
		this->SetSyncMutableState(true);
		m_scene->GetEventDispacher()->OnMoveObjectMoveAgentStateChange(this->GetSharedPtr<MoveObject>());
	}

	void MoveObject::OnVelocityChange(const Vector3 & old_val)
	{
		m_scene->GetEventDispacher()->OnMoveObjectVelocityChange(this->GetSharedPtr<MoveObject>(), old_val);

		this->SetSyncMutableState(true);
		if (NetProto::EMoveState_Move == this->GetMoveState())
		{
			Vector3 velocity = this->GetVelocity();
			if (abs(velocity.x) >= FLT_MIN || abs(velocity.z) >= FLT_MIN)
			{
				float angle = GeometryUtils::DeltaAngle(Vector2::up, velocity.xz());
				this->SetFaceDir(angle);

			}
		}
	}

	void MoveObject::OnPosChange(const Vector3 & old_val)
	{
		this->SetSyncMutableState(true);
	}

	void MoveObject::TryMoveToPos(const Vector3 &pos)
	{
		if (m_move_agent)
			m_move_agent->TryMoveToPos(pos);
	}

	void MoveObject::TryMoveToDir(float angle)
	{
		if (m_move_agent)
			m_move_agent->TryMoveToDir(angle);
	}

	void MoveObject::CancelMove()
	{
		if (m_move_agent)
			m_move_agent->CancelMove();
	}

	void MoveObject::CancelForceMove()
	{
		if (m_move_agent)
			m_move_agent->CancelForceMove();
	}

	void MoveObject::ForceMoveLine(const Vector2 & dir, float speed, float time_sec, bool ignore_terrian)
	{
		if (m_move_agent)
			m_move_agent->ForceMoveLine(dir, speed, time_sec, ignore_terrian);
	}

	void MoveObject::ForcePos(const Vector3 & destination, float speed)
	{
		if (m_move_agent)
			m_move_agent->ForcePos(destination, speed);
	}

	void MoveObject::ChangeForcePosDestination(const Vector3 & destination)
	{
		if (m_move_agent)
			m_move_agent->ChangeForcePosDestination(destination);
	}

	void MoveObject::Immobilized(long ms)
	{
		if (m_move_agent)
			m_move_agent->Immobilized(ms);
	}

	void MoveObject::CancelImmobilized()
	{
		if (m_move_agent)
			m_move_agent->CancelImmobilized();
	}

	void MoveObject::Flash(const Vector3 & val)
	{
		if (m_move_agent)
			m_move_agent->Flash(val);
	}

	NetProto::EMoveAgentState MoveObject::GetMoveAgentState()
	{
		return m_move_agent->GetMoveAgentState();
	}

	NetProto::EMoveState MoveObject::GetMoveState()
	{
		return m_move_agent->GetMoveState();
	}

	std::vector<SyncClientMsg> MoveObject::ColllectSyncClientMsg(int filter_type)
	{
		std::vector<SyncClientMsg> msgs;

		if (filter_type & SCMF_ForInit)
		{
			msgs.push_back(SyncClientMsg(NetProto::PID_MoveObjectState, this->GetPbMoveObjectState()));
		}
		if (filter_type & SCMF_ForMutable)
		{
			if (this->NeedSyncMutableState() || filter_type == SCMF_All)
			{
				msgs.push_back(SyncClientMsg(NetProto::PID_MoveObjectMutableState, this->GetPbMoveObjectMutableState()));
			}
		}

		return msgs;
	}

	NetProto::MoveObjectState * MoveObject::GetPbMoveObjectState()
	{
		NetProto::MoveObjectState *msg = m_scene->CreateProtobuf<NetProto::MoveObjectState>();
		msg->set_allocated_obj_state(this->GetPbSceneObjectState());
		msg->set_radius(this->GetBodyRadius());
		msg->set_height(m_body_height);
		msg->set_mass(0);
		msg->set_max_speed(m_speed);
		return msg;
	}

	NetProto::MoveObjectMutableState * MoveObject::GetPbMoveObjectMutableState()
	{
		NetProto::MoveObjectMutableState * msg = m_scene->CreateProtobuf<NetProto::MoveObjectMutableState>();
		auto pb_pos = msg->mutable_pos();
		pb_pos->set_x(m_pos.x);
		pb_pos->set_y(m_pos.y);
		pb_pos->set_z(m_pos.z);
		Vector3 volecity = this->GetVelocity();
		auto pb_volecity = msg->mutable_volecity();
		pb_volecity->set_x(volecity.x);
		pb_volecity->set_y(volecity.y);
		pb_volecity->set_z(volecity.z);
		msg->set_objid(m_id);
		msg->set_move_agent_state(this->GetMoveAgentState());
		msg->set_rotation(this->GetFaceDir());
		return msg;
	}

	void MoveObject::MoveStateChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent * agent, NetProto::EMoveAgentState old_state)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		ptr->OnMoveAgentStateChange(old_state);
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT + 2, "MoveStateChange:{0}->{1}", old_state, agent->GetMoveAgentState());
	}

	void MoveObject::PostChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_pos)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		ptr->SetPos(agent->GetPos());
		Vector3 pos = agent->GetPos();
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT, "OnPostChange [{}]:{:3.2f}, {:3.2f}, {:3.2f}", agent->GetMoveAgentState(), pos.x, pos.y, pos.z);
	}

	void MoveObject::VelocityChangeCb(std::weak_ptr<MoveObject> obj, MoveAgent * agent, Vector3 old_velocity)
	{
		auto ptr = obj.lock();
		if (nullptr == ptr)
			return;

		Vector3 velocity = agent->GetVelocity();
		ptr->OnVelocityChange(old_velocity);

		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT + 2, "OnVelocityChange [{}]:{:3.2f}, {:3.2f}, {:3.2f}", agent->GetMoveAgentState(), velocity.x, velocity.y, velocity.z);
	}
}

