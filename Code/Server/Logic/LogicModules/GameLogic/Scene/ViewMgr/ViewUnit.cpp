#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "ViewGrid.h"

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

		if (m_has_view)
		{
			for (auto view_grid : m_view_cover_girds)
			{
				--view_grid->m_observing_num[m_view_camp];
			}
		}
		m_view_cover_girds.clear();
		
		if (m_has_body)
		{
			for (auto view_grid : m_body_cover_girds)
			{
				view_grid->m_body_units.erase(m_objid);
			}
		}
		m_body_cover_girds.clear();
	}

	Vector2 ViewUnit::GetPos()
	{
		auto so = this->GetSceneObjSptr();
		if (nullptr != so)
			return so->GetPos().xz();
		return InvalidViewPos;
	}

	void ViewUnit::UpdateState()
	{

	}
}