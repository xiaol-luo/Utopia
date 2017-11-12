#pragma once

#include "ViewDefine.h"

namespace GameLogic
{
	class ViewVisualUnit
	{
	public:
		ViewVisualUnit(ViewMgr *view_mgr, std::shared_ptr<SceneObject> scene_obj);
		~ViewVisualUnit();

		uint64_t GetObjId() { return m_objid; }
		std::shared_ptr<SceneObject> GetSceneObj() { return m_scene_obj.lock(); }
		Vector2 GetPos();

	private:
		uint64_t m_objid = 0;
		std::weak_ptr<SceneObject> m_scene_obj;
		ViewMgr *m_view_mgr = nullptr;
	};
}
