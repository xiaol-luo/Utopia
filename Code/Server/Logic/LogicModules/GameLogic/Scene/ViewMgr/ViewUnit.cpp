#include "ViewUnit.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"
#include "ViewGrid.h"
#include "ViewMgr.h"

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
		m_view_camp = scene_obj->GetViewCamp();
		m_has_body = true;
		m_has_view = true;
		return true;
	}

	void ViewUnit::Reset()
	{
		if (!m_has_view && !m_has_body)
			return;

		m_view_mgr = nullptr;
		auto scene_obj = m_scene_obj.lock();
		if (nullptr != scene_obj && scene_obj->GetViewUnit() == this)
				scene_obj->SetViewUnit(nullptr);
		m_scene_obj.reset();
		m_objid = 0;
		m_view_camp = EViewCamp_None;
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

		m_has_body = false;
		m_has_view = false;
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
		std::shared_ptr<SceneObject> so = m_scene_obj.lock();
		if (nullptr == so)
		{
			this->Reset();
			return;
		}

		Vector3 pos = so->GetPos();
		ViewGrid *locate_grid = m_view_mgr->GetGrid(pos.x, pos.z);
		bool needUpdate = (nullptr == locate_grid || nullptr == m_locate_grid || locate_grid != m_locate_grid);
		if (!needUpdate)
			return;

		m_locate_grid = locate_grid;
		Vector2 locate_pos = m_locate_grid->m_center;

		if (m_has_view)
		{
			ViewGridVec cover_grids = m_view_mgr->GetCircleCoverGrids(locate_pos.x, locate_pos.y, so->GetViewRadius());
			for (auto grid : m_view_cover_girds)
			{
				--grid->m_observing_num[m_view_camp];
			}
			m_view_cover_girds = cover_grids;
			for (auto grid : m_view_cover_girds)
			{
				++grid->m_observing_num[m_view_camp];
			}
		}
		if (m_has_body)
		{
			ViewGridVec cover_grids = m_view_mgr->GetCircleCoverGrids(locate_pos.x, locate_pos.y, so->GetBodyRadius());
			for (auto grid : m_body_cover_girds)
			{
				grid->m_body_units.erase(m_objid);
			}
			m_body_cover_girds = cover_grids;
			for (auto grid : m_body_cover_girds)
			{
				grid->m_body_units.insert(std::make_pair(m_objid, this));
			}
		}
	}
}