#pragma once

#include <stdint.h>

namespace GameLogic
{
	class Scene;

	class SceneObject
	{
	public: 
		SceneObject();
		virtual ~SceneObject();

	public:
		void SetScene(Scene *scene) { m_scene = scene; }
		Scene * GetScene() { return m_scene; }
		uint64_t GetId() { return m_id; }
		void SetId(uint64_t id) { m_id = id; }
		void LeaveScene();
		void OnEnterScene(Scene *scene);
		void OnLeaveScene(Scene *scene);
		void Update(long long now_ms);
	protected:
		Scene *m_scene = nullptr;
		uint64_t m_id = 0;
	};
}