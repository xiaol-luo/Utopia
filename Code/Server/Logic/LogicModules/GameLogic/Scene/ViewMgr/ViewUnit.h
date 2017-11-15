#pragma once

#include "ViewDefine.h"
#include "GameLogic/Scene/Defines/SceneDefine.h"

namespace GameLogic
{
	class ViewUnit
	{
	public:
		ViewUnit();
		~ViewUnit();

		bool Init(ViewMgr *view_mgr, std::shared_ptr<SceneObject> scene_obj);
		void Reset();

		uint64_t GetObjId() { return m_objid; }
		std::shared_ptr<SceneObject> GetSceneObjSptr() { return m_scene_obj.lock(); }
		std::weak_ptr<SceneObject> GetSceneObjWptr() { return m_scene_obj; }
		Vector2 GetPos();
		
		void UpdateState();

	private:
		ViewMgr *m_view_mgr = nullptr;
		uint64_t m_objid = 0;
		std::weak_ptr<SceneObject> m_scene_obj;
		ViewGrid *m_locate_grid = nullptr;

		// body
		bool m_has_body = false;
		ESceneObjectShape m_body_shape = ESceneObjectShape_Circle;
		float m_body_size_x = 0.0f;
		float m_body_size_y = 0.0f;
		float m_face_dir = 0.0f;
		ViewGridVec m_body_cover_girds;
		
		// view
		bool m_has_view = false;
		float m_view_radius = 0.0f;
		EViewCamp m_view_camp = EViewCamp_None;
		ViewGridVec m_view_cover_girds;
	};
}