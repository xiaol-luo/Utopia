#include "SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModules/SceneUnitMove.h"

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
		this->GetEvProxy()->Fire<Vector3, Vector3>(ESU_PosChange, old_Pos, this->GetPos());

		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT,
		"SceneUnitTransform::SetLocalPos {:3.2f}, {:3.2f}, {:3.2f}", m_local_pos.x, m_local_pos.y, m_local_pos.z);
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
	void SceneUnitTransform::SetFaceDir(const Vector2 &face_dir)
	{
		m_face_dir = face_dir;
		m_face_dir.normalize();
	}
	const Vector2 & SceneUnitTransform::GetFaceDir()
	{
		return m_face_dir;
	}

	void SceneUnitTransform::SetFaceAngle(float face_angle)
	{
	}

	float SceneUnitTransform::GetFaceAngle()
	{
		return 0.0f;
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
				this->SetFaceDir(new_val.xz());
			}
		}
	}
}