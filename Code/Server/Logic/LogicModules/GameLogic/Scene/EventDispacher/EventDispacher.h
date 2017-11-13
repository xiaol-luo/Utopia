#pragma once

#include <memory>

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
		void OnAddSceneObject(std::shared_ptr<SceneObject> scene_obj);
		void OnRemoveSceneObject(std::shared_ptr<SceneObject> scene_obj);
		void OnMoveObjectMoveAgentStateChange(std::shared_ptr<MoveObject> move_obj);
		void OnMoveObjectVelocityChange(std::shared_ptr<MoveObject> move_obj);
		void OnSceneObjectPosChange(std::shared_ptr<SceneObject> move_obj);

	private:
		Scene *m_scene = nullptr;
	};
}
