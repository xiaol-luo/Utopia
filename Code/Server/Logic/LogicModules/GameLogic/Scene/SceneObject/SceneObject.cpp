#include "SceneObject.h"
#include "GameLogic/Scene/Scene.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"

namespace GameLogic
{
	SceneObject::SceneObject(ESceneObjectType obj_type) : m_scene(nullptr), m_id(Scene::INVALID_SCENE_OBJID), m_obj_type(obj_type)
	{
	}

	SceneObject::~SceneObject()
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

	void SceneObject::SetRotation(float val)
	{
		if (abs(val - m_rotation) < FLT_EPSILON)
			return;

		float old_val = m_rotation;
		m_rotation = val;
		this->OnRotationChange(old_val);
	}

	std::vector<SyncClientMsg> SceneObject::ColllectSyncClientMsg(int filter_type)
	{
		std::vector<SyncClientMsg> client_msgs;
		if (filter_type & SCMF_ForInit)
		{
			NetProto::SceneObjectState * msg = m_scene->CreateProtobuf<NetProto::SceneObjectState>();
			msg->set_model_id(m_model_id);
			msg->set_obj_type((::NetProto::SceneObjectType)m_obj_type);
			msg->set_objid(m_id);
			auto pos = msg->mutable_pos();
			pos->set_x(m_pos.x);
			pos->set_y(m_pos.y);
			pos->set_z(m_pos.z);
			client_msgs.push_back(SyncClientMsg(NetProto::PID_SceneObjectState, msg));
		}

		return std::move(client_msgs);
	}

	void SceneObject::OnPosChange(const Vector3 &old_val)
	{

	}

	void SceneObject::OnRotationChange(float old_val)
	{
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
}