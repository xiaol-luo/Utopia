#include "SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace GameLogic
{
	SceneUnitTransform::SceneUnitTransform() : SceneUnitModule(ESceneUnitModule_Transform)
	{
	}
	SceneUnitTransform::~SceneUnitTransform()
	{
	}
	bool SceneUnitTransform::SetParent(std::shared_ptr<SceneUnitTransform> parent)
	{
		/*
		// 限制parent不能有parent,限制this不能有child, 所以只有两层防止闭环
		if (nullptr != parent && !parent->m_parent.expired()) 
			return false;
		if (nullptr != parent && !this->m_children.empty())
			return false;
		*/

		if (this->CheckLoop(parent))
			return false;

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
		m_local_pos = pos;
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
}