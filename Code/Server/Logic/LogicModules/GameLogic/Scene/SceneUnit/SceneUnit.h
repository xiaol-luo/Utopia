#pragma once

#include <memory>
#include "GameLogic/Scene/Defines/SceneDefine.h"
#include <assert.h>
#include "Network/Protobuf/BattleEnum.pb.h"

class EventDispacher;
class EventDispacherProxy;

namespace GameLogic
{
	class NewScene;
	class SceneUnitTransform;
	class SceneUnitModule;
	class SceneUnitEventProxy;

	class SceneUnit : public std::enable_shared_from_this<SceneUnit>
	{
	public:
		SceneUnit();
		~SceneUnit();
		
		template <typename T>
		std::shared_ptr<T> AddModule(std::shared_ptr<T> module)
		{
			assert(!m_inited);
			assert(nullptr == m_modules[module->GetModuleName()]);
			m_modules[module->GetModuleName()] = module;
			module->m_owner = this;
			return module;
		}

		void EnterScene(NewScene *scene, uint64_t id);
		void LeaveScene();
		void Update();

		NewScene * GetScene() { return m_scene; }
		EventDispacher * GetEvDispacher() { return m_event_dispacher; }
		SceneUnitEventProxy * GetEvProxy() { return m_event_proxy; }
		EventDispacherProxy * GetSceneEvProxy() { return m_scene_event_proxy; }

		template <typename T>
		std::shared_ptr<T> GetModule()
		{
			std::shared_ptr<T> ptr = nullptr;
			int idx = T::MODULE_TYPE;
			if (idx  >= 0 && idx < ESceneUnitModule_Count)
				ptr = std::dynamic_pointer_cast<T>(m_modules[idx]);
			return ptr;
		}

		std::shared_ptr<SceneUnitTransform> GetTransform();

	public:
		uint64_t GetId() { return m_id; }
		uint64_t GetPlayerId() { return m_player_id; }
		void SetPlayerId(uint64_t player_id) { m_player_id = player_id; }
		int GetModelId() { return m_model_id; }
		void SetModelId(int val) { m_model_id = val; }
		NetProto::ESceneUnitType GetUnitType() { return m_unit_type; }
		void SetUnitType(NetProto::ESceneUnitType unit_type) { m_unit_type = unit_type; }
		NetProto::ESceneUnitCamp GetCamp() { return m_camp; }
		void SetCamp(NetProto::ESceneUnitCamp val) { m_camp = val; }
		std::vector<SyncClientMsg> CollectPBInit();
		std::vector<SyncClientMsg> CollectPbMutable();

	private:
		NewScene *m_scene = nullptr;
		uint64_t m_id = 0;
		uint64_t m_player_id = 0;
		NetProto::ESceneUnitType m_unit_type = NetProto::EsceneUnitType_Unknown;
		NetProto::ESceneUnitCamp m_camp = NetProto::ESceneUnitCamp_Neutral;
		int m_model_id = 0;
		
		bool m_inited = false;
		bool m_started = false;
		bool m_inScene = false;
		std::shared_ptr<SceneUnitModule> m_modules[ESceneUnitModule_Count];
		std::shared_ptr<SceneUnitTransform> m_transform = nullptr;

		EventDispacher *m_event_dispacher = nullptr;
		EventDispacherProxy *m_scene_event_proxy = nullptr;
		SceneUnitEventProxy *m_event_proxy = nullptr;

	public:
		void SendSelf(int protocol_id, google::protobuf::Message *msg);
		void SendSelf(const std::vector<SyncClientMsg> &msgs);
		void SendObservers(int protocol_id, google::protobuf::Message *msg);
		void SendObservers(const std::vector<SyncClientMsg> &msgs);
		void ClearPbDirty();
	};
}