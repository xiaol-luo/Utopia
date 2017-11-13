#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"

namespace GameLogic
{
	ViewUnit::ViewUnit()
	{
	}
	ViewUnit::~ViewUnit()
	{
	}

	bool ViewUnit::Init(ViewMgr *view_mgr, std::shared_ptr<SceneObject> scene_obj)
	{
		m_view_mgr = view_mgr;
		m_scene_obj = scene_obj;
		m_objid = scene_obj->GetId();
		return true;
	}

	Vector2 ViewUnit::GetPos()
	{
		auto so = this->GetSceneObj();
		if (nullptr != so)
			return so->GetPos().xz();
		return InvalidViewPos;
	}
}