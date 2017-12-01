#pragma once

#include <unordered_map>
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitModule.h"

namespace GameLogic
{
	class SceneUnitTransform : public SceneUnitModule
	{
	public:
		static const ESceneUnitModule MODULE_TYPE = ESceneUnitModule_Transform;
	public: 
		SceneUnitTransform();
		virtual ~SceneUnitTransform() override;

	public:
		bool SetParent(std::shared_ptr<SceneUnitTransform> parent);
		bool AddChild(std::shared_ptr<SceneUnitTransform> child);
		void RemoveChild(uint64_t id);
		void ClearChildren();
		void Deattach();
		bool CheckLoop(std::weak_ptr<SceneUnitTransform> parent);
	protected:
		bool CheckLoopHelp(std::weak_ptr<SceneUnitTransform> parent, uint64_t cmp_id);
		std::weak_ptr<SceneUnitTransform> m_parent;
		std::unordered_map<uint64_t, std::weak_ptr<SceneUnitTransform>> m_children;
		
	public:
		void SetLocalPos(const Vector3 &pos);
		const Vector3 & GetLocalPos();
		Vector3 GetPos();
		void SetFaceDir(const Vector2 &face_dir);
		const Vector2 & GetFaceDir();
		void SetFaceAngle(float face_angle);
		float GetFaceAngle();

	protected:
		Vector2 m_face_dir;
		Vector3 m_local_pos;

	protected:
		virtual void OnAwake() override;
		void OnMoveVolecityChange(Vector3 old_val, Vector3 new_pos);

	public:
		virtual std::vector<SyncClientMsg> CollectPBInit() override;
		virtual std::vector<SyncClientMsg> CollectPbMutable() override;
	};
}
