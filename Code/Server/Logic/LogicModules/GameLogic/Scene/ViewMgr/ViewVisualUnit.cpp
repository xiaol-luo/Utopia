#include "ViewVisualUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "ViewMgr.h"
#include "ViewDefine.h"

namespace GameLogic
{
	ViewVisualUnit::ViewVisualUnit(ViewMgr *view_mgr, std::shared_ptr<SceneObject> scene_obj)
	{
		m_scene_obj = scene_obj;
		m_objid = scene_obj->GetId();
		m_view_mgr = view_mgr;
	}

	ViewVisualUnit::~ViewVisualUnit()
	{

	}

	Vector2 ViewVisualUnit::GetPos()
	{
		auto so = this->GetSceneObj();
		if (nullptr != so)
			return so->GetPos().xz();
		return InvalidViewPos;
	}
}


