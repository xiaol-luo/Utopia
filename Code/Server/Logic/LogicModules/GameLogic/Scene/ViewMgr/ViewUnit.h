#pragma once

#include "ViewDefine.h"
#include "GameLogic/Scene/SceneDefine.h"

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
		std::shared_ptr<SceneObject> GetSceneObj() { return m_scene_obj.lock(); }
		Vector2 GetPos();

		inline void SetVisualChange(bool val=true) { m_visual_change = val; }
		bool IsVisualChange() { return m_visual_change; }
		inline void SetViewChange(bool val=true) { m_view_change = val; }
		bool IsViewChange() { return m_view_change; }

	private:
		ViewMgr *m_view_mgr = nullptr;
		uint64_t m_objid = 0;
		std::weak_ptr<SceneObject> m_scene_obj;
		ViewGrid *m_locate_grid = nullptr;

		// body
		bool m_has_body = false;
		bool m_visual_change = true;
		ESceneObjectShape m_body_shape = ESceneObjectShape_CirCle;
		float m_body_size_x = 0.0f;
		float m_body_size_y = 0.0f;
		float m_face_dir = 0.0f;
		ViewGridSet m_body_cover_girds;
		
		// view
		bool m_has_view = false;
		bool m_view_change = true;
		float m_view_radius = 0.0f;
		EViewCamp m_view_camp = EViewCamp_None;
		ViewGridSet m_view_cover_girds;
	};
}