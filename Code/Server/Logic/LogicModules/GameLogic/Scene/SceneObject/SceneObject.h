#pragma once

#include <stdint.h>
#include <vector>
#include "Common/Geometry/Vector3.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentState.h"
#include "google/protobuf/message.h"
#include "GameLogic/Scene/Defines/SceneDefine.h"
#include "GameLogic/Scene/ViewMgr/ViewDefine.h"

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
		float GetNavBodyRadius() { return m_nav_radius; }
		ViewUnit * GetViewUnit() { return m_view_unit; }
		void SetViewUnit(ViewUnit *view_unit) { m_view_unit = view_unit; }
		float GetViewRadius() { return m_view_radius; }
		EViewCamp GetViewCamp() { return m_view_camp; }
		void SetViewCamp(EViewCamp val) { m_view_camp = val; }
	protected:
		Scene *m_scene = nullptr;
		uint64_t m_id = 0;
		ESceneObjectType m_obj_type = ESOT_Max;
		int m_model_id = 0;
		Vector3 m_pos;
		float m_face_dir = 0;
		float m_nav_radius = 0.5f;
		ESceneObjectShape m_body_shape = ESceneObjectShape_Circle;
		float m_body_size_x = 0.0f;
		float m_body_size_y = 0.0f;
		float m_view_radius = 1.0f;
		float m_body_scale = 1.0f;
		float m_body_radius = 1.0f;
		bool m_has_body = true;
		bool m_has_view = true;
		EViewCamp m_view_camp = EViewCamp_None;
		ViewUnit *m_view_unit = nullptr;

	public:
		virtual std::vector<SyncClientMsg> ColllectSyncClientMsg(int filter_type, bool include_unchanged);
		inline bool NeedSyncClient() { return 0 != m_sync_client_flag; }
		inline bool NeedSyncClient(SyncClientMsgFilter val) { return m_sync_client_flag & val; }
		inline void SetSyncClientFlag(SyncClientMsgFilter val) { m_sync_client_flag |= val; }
		inline void ClearSyncClientFlag() { m_sync_client_flag = 0; }
	protected:
		NetProto::SceneObjectState * GetPbSceneObjectState();
		uint64_t m_sync_client_flag  = 0;
	};
}