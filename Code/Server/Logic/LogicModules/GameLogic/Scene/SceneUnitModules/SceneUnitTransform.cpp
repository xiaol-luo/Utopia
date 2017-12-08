#include "SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "Network/Protobuf/Battle.pb.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/NewScene.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "Common/Geometry/GeometryUtils.h"

namespace GameLogic
{
	SceneUnitTransform::SceneUnitTransform() : SceneUnitModule(MODULE_TYPE)
	{
	}
	SceneUnitTransform::~SceneUnitTransform()
	{
	}
	bool SceneUnitTransform::SetParent(std::shared_ptr<SceneUnitTransform> parent)
	{
		if (this->CheckLoop(parent))
		{
			GlobalServerLogic->GetLogModule()->Error(LogModule::LOGGER_ID_STDERR,
				"SetParent wiil Loop parent:{0}, child:{1}", parent->GetId(), this->GetId());
			return false;
		}

		std::shared_ptr<SceneUnitTransform> curr_parent = m_parent.lock();
		if (nullptr != curr_parent)
		{
			if (nullptr != parent && curr_parent->GetId() == parent->GetId())
				return true;
			curr_parent->m_children.erase(this->GetId());
		}
		m_parent.reset();
		if (nullptr != parent)
		{
			m_parent = parent;
			parent->m_children.insert(std::make_pair(this->GetId(), this->GetSharedPtr<SceneUnitTransform>()));
		}

		return true;
	}
	bool SceneUnitTransform::AddChild(std::shared_ptr<SceneUnitTransform> child)
	{
		if (nullptr == child)
			return false;
		return child->SetParent(this->GetSharedPtr<SceneUnitTransform>());
	}
	void SceneUnitTransform::RemoveChild(uint64_t id)
	{
		auto it = m_children.find(id);
		if (m_children.end() == it)
			return;
		auto child = it->second.lock();
		it = m_children.end();
		child->SetParent(nullptr);
	}
	void SceneUnitTransform::ClearChildren()
	{
		std::vector<uint64_t> child_ids;
		for (auto kv_pair : m_children)
			child_ids.push_back(kv_pair.first);
		for (uint64_t id : child_ids)
			this->RemoveChild(id);
	}
	void SceneUnitTransform::Deattach()
	{
		this->ClearChildren();
		this->SetParent(nullptr);
	}
	bool SceneUnitTransform::CheckLoop(std::weak_ptr<SceneUnitTransform> parent)
	{
		return this->CheckLoopHelp(parent, this->GetId());
	}
	bool SceneUnitTransform::CheckLoopHelp(std::weak_ptr<SceneUnitTransform> parent, uint64_t cmp_id)
	{
		auto sptr_parent = parent.lock();
		if (nullptr == sptr_parent)
			return false;
		if (sptr_parent->GetId() == cmp_id)
			return true;
		return this->CheckLoopHelp(sptr_parent->m_parent, cmp_id);
	}
	void SceneUnitTransform::SetLocalPos(const Vector3 & pos)
	{
		Vector3 old_Pos = this->GetPos();
		m_local_pos = pos;
		this->SetPbDirty();

		if (nullptr != m_owner->GetScene())
			this->GetEvProxy()->Fire<Vector3, Vector3>(ESU_PosChange, old_Pos, this->GetPos());

		/*
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
		"SceneUnitTransform::SetLocalPos {:3.2f}, {:3.2f}, {:3.2f}", m_local_pos.x, m_local_pos.y, m_local_pos.z);
		*/
	}
	const Vector3 & SceneUnitTransform::GetLocalPos()
	{
		return m_local_pos;
	}
	Vector3 SceneUnitTransform::GetPos()
	{
		auto parent = m_parent.lock();
		if (nullptr != parent)
			return m_local_pos + parent->GetPos();
		return m_local_pos;

	}
	void SceneUnitTransform::SetFaceDir(const Vector2 &face_dir, ESUFaceDir e_dir)
	{
		if (e_dir < 0 || e_dir >= ESUFaceDir_Count)
			return;

		m_face_dir[e_dir] = face_dir;
		m_face_dir[e_dir].normalize();
		this->SetPbDirty();
	}

	Vector2 SceneUnitTransform::GetFaceDir()
	{
		Vector2 face_dir = Vector2::up;
		for (int i = ESUFaceDir_Count - 1; i >= 0; --i)
		{
			if (Vector2::zero != m_face_dir[i])
			{
				face_dir = m_face_dir[i];
				break;
			}
		}
		return std::move(face_dir);
	}

	void SceneUnitTransform::SetFaceAngle(float face_angle, ESUFaceDir e_dir)
	{
		Vector2 face_dir = GeometryUtils::CalVector2(Vector2::up, face_angle);
		this->SetFaceDir(face_dir, e_dir);
	}

	float SceneUnitTransform::GetFaceAngle()
	{
		Vector2 face_dir = this->GetFaceDir();
		float angle = GeometryUtils::DeltaAngle(Vector2::up, face_dir);
		return angle;
	}

	void SceneUnitTransform::OnAwake()
	{
		this->GetEvProxy()->Subscribe<Vector3, Vector3>(ESU_VolecityChange, 
			std::bind(&SceneUnitTransform::OnMoveVolecityChange,
			this, std::placeholders::_1, std::placeholders::_2));		
	}

	void SceneUnitTransform::OnMoveVolecityChange(Vector3 old_val, Vector3 new_val)
	{
		auto move_state = m_owner->GetModule<SceneUnitMove>()->GetMoveState();
		if (NetProto::EMoveState_Move == move_state)
		{
			if (abs(new_val.x) > FLT_EPSILON || (abs(new_val.z) > FLT_EPSILON))
			{
				this->SetFaceDir(new_val.xz(), ESUFaceDir_Move);
			}
		}
	}
	std::vector<SyncClientMsg> SceneUnitTransform::CollectPBInit()
	{
		std::vector<SyncClientMsg> msgs;
		{
			NetProto::SceneUnitState *msg = m_owner->GetScene()->CreateProtobuf<NetProto::SceneUnitState>();
			msg->set_su_id(this->GetId());
			msg->set_unit_type(m_owner->GetUnitType());
			msg->set_model_id(m_owner->GetModelId());
			NetProto::PBVector3 *pb_pos = msg->mutable_pos();
			pb_pos->set_x(m_local_pos.x);
			pb_pos->set_y(m_local_pos.y);
			pb_pos->set_z(m_local_pos.z);
			msg->set_face_dir(this->GetFaceAngle());
			auto parent = m_parent.lock();
			if (nullptr != parent)
				msg->set_parent_su_id(parent->GetId());
			msgs.push_back(SyncClientMsg(NetProto::PID_SceneUnitState, msg));
		}
		return std::move(msgs);
	}
	std::vector<SyncClientMsg> SceneUnitTransform::CollectPbMutable()
	{
		std::vector<SyncClientMsg> msgs;
		{
			NetProto::SceneUnitTransform *msg = m_owner->GetScene()->CreateProtobuf<NetProto::SceneUnitTransform>();
			msg->set_su_id(this->GetId());
			NetProto::PBVector3 *pb_pos = msg->mutable_pos();
			pb_pos->set_x(m_local_pos.x);
			pb_pos->set_y(m_local_pos.y);
			pb_pos->set_z(m_local_pos.z);
			msg->set_face_dir(this->GetFaceAngle());
			auto parent = m_parent.lock();
			if (nullptr != parent)
				msg->set_parent_su_id(parent->GetId());
			msgs.push_back(SyncClientMsg(NetProto::PID_SceneUnitTransform, msg));
		}
		return std::move(msgs);
	}
}