#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"

namespace GameLogic
{
	ViewUnit::ViewUnit()
	{
	}

	ViewUnit::~ViewUnit()
	{
		this->Reset();
	}

	bool ViewUnit::Init(ViewMgr *view_mgr, std::shared_ptr<SceneObject> scene_obj)
	{
		this->Reset();
		m_view_mgr = view_mgr;
		m_scene_obj = scene_obj;
		m_objid = scene_obj->GetId();
		return true;
	}

	void ViewUnit::Reset()
	{
		m_view_mgr = nullptr;
		auto scene_obj = m_scene_obj.lock();
		if (nullptr != scene_obj && scene_obj->GetViewUnit() == this)
				scene_obj->SetViewUnit(nullptr);
		m_scene_obj.reset();
		m_objid = 0;
	}

	Vector2 ViewUnit::GetPos()
	{
		auto so = this->GetSceneObjSptr();
		if (nullptr != so)
			return so->GetPos().xz();
		return InvalidViewPos;
	}
}