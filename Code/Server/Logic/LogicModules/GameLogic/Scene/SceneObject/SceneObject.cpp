#include "SceneObject.h"
#include "GameLogic/Scene/Scene.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "GameLogic/Scene/EventDispacher/SceneEventDispacher.h"

namespace GameLogic
{
	SceneObject::SceneObject(ESceneObjectType obj_type) : m_scene(nullptr), m_id(Scene::INVALID_SCENE_OBJID), m_obj_type(obj_type)
	{
	}

	SceneObject::~SceneObject()
	{
		this->SetViewUnit(nullptr);
	}

	void SceneObject::OnPosChange(const Vector3 &old_val)
	{
		m_scene->GetEventDispacher()->OnSceneObjectPosChange(this->shared_from_this(), old_val);
	}

	void SceneObject::OnFaceDirChange(float old_val)
	{
		m_scene->GetEventDispacher()->OnSceneObjectFaceDirChange(this->shared_from_this(), old_val);
	}

	void SceneObject::OnEnterScene(Scene *scene)
	{

	}

	void SceneObject::OnLeaveScene(Scene *scene)
	{

	}

	void SceneObject::Update(long long now_ms)
	{

	}

	void SceneObject::LeaveScene()
	{
		if (nullptr != m_scene)
		{
			m_scene->RemoveObject(m_id);
		}
	}

	void SceneObject::SetPos(const Vector3 & val)
	{
		if (val == m_pos)
			return;

		Vector3 old_pos = m_pos;
		m_pos = val;
		this->OnPosChange(old_pos);
	}

	void SceneObject::SetFaceDir(float val)
	{
		if (abs(val - m_face_dir) < FLT_EPSILON)
			return;

		float old_val = m_face_dir;
		m_face_dir = val;
		this->OnFaceDirChange(old_val);
	}

	float SceneObject::GetBodyRadius()
	{
		return m_body_radius * m_body_scale;
	}

	std::vector<SyncClientMsg> SceneObject::ColllectSyncClientMsg(int filter_type, bool include_unchanged)
	{
		std::vector<SyncClientMsg> client_msgs;
		if ((filter_type & SCMF_ForInit) && (include_unchanged || this->NeedSyncClient(SCMF_ForInit)))
		{
			client_msgs.push_back(SyncClientMsg(NetProto::PID_SceneObjectState, this->GetPbSceneObjectState()));
		}
		return std::move(client_msgs);
	}

	NetProto::SceneObjectState * SceneObject::GetPbSceneObjectState()
	{
		NetProto::SceneObjectState * msg = m_scene->CreateProtobuf<NetProto::SceneObjectState>();
		msg->set_model_id(m_model_id);
		msg->set_obj_type((::NetProto::ESceneObject)m_obj_type);
		msg->set_objid(m_id);
		msg->set_rotation(m_face_dir);
		auto pos = msg->mutable_pos();
		pos->set_x(m_pos.x);
		pos->set_y(m_pos.y);
		pos->set_z(m_pos.z);
		return msg;
	}
}