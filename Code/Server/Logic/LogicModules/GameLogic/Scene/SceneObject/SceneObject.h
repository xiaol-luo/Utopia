#pragma once

#include <stdint.h>
#include <vector>
#include "Common/Geometry/Vector3.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentState.h"
#include "google/protobuf/message.h"
#include "GameLogic/Scene/SceneDefine.h"

namespace NetProto
{
	class SceneObjectState;
}

namespace GameLogic
{
	class Scene;
	class MoveAgent;
	class ViewUnit;

	enum ESceneObjectType
	{
		ESOT_Npc,
		ESOT_Hero,

		ESOT_Max,
	};

	struct SyncClientMsg
	{
		SyncClientMsg(int id, google::protobuf::Message *_msg) : protocol_id(id), msg(_msg) {}
		int protocol_id;
		google::protobuf::Message *msg;
	};

	class SceneObject : public std::enable_shared_from_this<SceneObject>
	{
	public: 
		SceneObject(ESceneObjectType obj_type);
		virtual ~SceneObject();
		virtual void OnEnterScene(Scene *scene);
		virtual void OnLeaveScene(Scene *scene);
		virtual void Update(long long now_ms);

	protected:
		template <typename T>
		std::shared_ptr<T> GetSharedPtr()
		{
			return std::dynamic_pointer_cast<T>(shared_from_this());
		}
		template <typename T>
		std::shared_ptr<T> GetSharedPtr() const
		{
			return std::dynamic_pointer_cast<T>(shared_from_this());
		}
		virtual void OnPosChange(const Vector3 &old_val);
		virtual void OnFaceDirChange(float old_val);

	public:
		void LeaveScene();
		void SetScene(Scene *scene) { m_scene = scene; }
		Scene * GetScene() { return m_scene; }
		uint64_t GetId() { return m_id; }
		void SetId(uint64_t id) { m_id = id; }
		uint64_t GetModelId() { return m_model_id; }
		void SetModelId(uint64_t val) { m_model_id = val; }
		ESceneObjectType GetObjectType() { return m_obj_type; }
		inline const Vector3 & GetPos() { return m_pos; }
		void SetPos(const Vector3 &val);
		inline float GetFaceDir() { return m_face_dir; }
		void SetFaceDir(float val);
		float GetBodyRadius();
		ViewUnit * GetViewUnit() { return m_view_unit; }
		void SetViewUnit(ViewUnit *view_unit) { m_view_unit = view_unit; }
	protected:
		Scene *m_scene = nullptr;
		uint64_t m_id = 0;
		ESceneObjectType m_obj_type = ESOT_Max;
		int m_model_id = 0;
		Vector3 m_pos;
		float m_face_dir = 0;
		ESceneObjectShape m_body_shape = ESceneObjectShape_Circle;
		float m_body_size_x = 0.0f;
		float m_body_size_y = 0.0f;
		float m_view_radius = 0.0f;
		float m_body_scale = 1.0f;
		float m_body_radius = 0.4f;
		bool m_has_body = true;
		bool m_has_view = true;
		ViewUnit *m_view_unit = nullptr;

	public:
		virtual std::vector<SyncClientMsg> ColllectSyncClientMsg(int filter_type);
		bool NeedSyncMutableState() { return m_flag_sync_mutable_state; }
		void SetSyncMutableState(bool val) { m_flag_sync_mutable_state = val; }
	protected:
		NetProto::SceneObjectState * GetPbSceneObjectState();
		bool m_flag_sync_mutable_state = false;
	};
}