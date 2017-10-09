#pragma once

#include <stdint.h>
#include "Common/Math/Vector3.h"

namespace GameLogic
{
	class Scene;

	enum ESceneObjectType
	{
		ESOT_Npc,
		ESOT_Hero,

		ESOT_Max,
	};

	class SceneObject
	{
	public: 
		SceneObject(ESceneObjectType obj_type);
		virtual ~SceneObject();

	public:
		virtual void OnEnterScene(Scene *scene);
		virtual void OnLeaveScene(Scene *scene);
		virtual void Update(long long now_ms);

	public:
		void LeaveScene();
		void SetScene(Scene *scene) { m_scene = scene; }
		Scene * GetScene() { return m_scene; }
		uint64_t GetId() { return m_id; }
		void SetId(uint64_t id) { m_id = id; }
		ESceneObjectType GetObjectType() { return m_obj_type; }
		inline Vector3 GetPosition() { return m_position; }
		inline void setPosition(const Vector3 &val) { m_position = val; }
		inline float getRotation() { return m_rotation; }
		inline void setRotation(float val) { m_rotation = val; }
	protected:
		Scene *m_scene = nullptr;
		uint64_t m_id = 0;
		ESceneObjectType m_obj_type = ESOT_Max;
		Vector3 m_position;
		float m_rotation;
	};
}