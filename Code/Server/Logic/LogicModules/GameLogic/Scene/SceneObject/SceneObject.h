#pragma once

#include <stdint.h>
#include <vector>
#include "Common/Geometry/Vector3.h"
#include "GameLogic/Scene/MoveMgr/MoveAgentState/MoveAgentState.h"
#include "google/protobuf/message.h"

namespace NetProto
{
	class SceneObjectState;
}

namespace GameLogic
{
	class Scene;
	class MoveAgent;

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
		uint64_t GetModelId() { return m_model_id; }
		void SetModelId(uint64_t val) { m_model_id = val; }
		ESceneObjectType GetObjectType() { return m_obj_type; }
		inline const Vector3 & GetPos() { return m_pos; }
		void SetPos(const Vector3 &val);
		inline float GetRotation() { return m_rotation; }
		void SetRotation(float val);
		bool NeedSyncMutableState() { return m_flag_sync_mutable_state; }
		void SetSyncMutableState(bool val) { m_flag_sync_mutable_state = val; }
		virtual std::vector<SyncClientMsg> ColllectSyncClientMsg(int filter_type);

	protected:
		NetProto::SceneObjectState * GetPbSceneObjectState();

	protected:
		virtual void OnPosChange(const Vector3 &old_val);
		virtual void OnRotationChange(float old_val);

	protected:
		Scene *m_scene = nullptr;
		uint64_t m_id = 0;
		ESceneObjectType m_obj_type = ESOT_Max;
		int m_model_id = 0;
		Vector3 m_pos;
		float m_rotation;

		bool m_flag_sync_mutable_state = false;
	};
}