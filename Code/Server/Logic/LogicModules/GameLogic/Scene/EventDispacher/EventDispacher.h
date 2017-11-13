#pragma once

#include <memory>
#include "Common/Geometry/Vector3.h"

namespace GameLogic
{
	class Scene;
	class SceneObject;
	class MoveObject;

	class SceneEventDispacher
	{
	public: 
		SceneEventDispacher(Scene *scene);
		~SceneEventDispacher();

	public:
		void OnSceneAddObject(std::shared_ptr<SceneObject> scene_obj);
		void OnSceneRemoveObject(std::shared_ptr<SceneObject> scene_obj);
		void OnMoveObjectMoveAgentStateChange(std::shared_ptr<MoveObject> move_obj);
		void OnMoveObjectVelocityChange(std::shared_ptr<MoveObject> move_obj, Vector3 old_velocity);
		void OnSceneObjectPosChange(std::shared_ptr<SceneObject> scene_obj, Vector3 old_pos);
		void OnSceneObjectFaceDirChange(std::shared_ptr<SceneObject> scene_obj, float old_face_dir);

	private:
		Scene *m_scene = nullptr;
	};
}
