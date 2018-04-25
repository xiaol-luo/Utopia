#pragma once

#include <memory>
#include "GameLogic/Scene/Defines/SceneDefine.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

class EventDispacherProxy;

namespace GameLogic
{
	class SceneUnitEventProxy;

	class SceneUnitModule : public std::enable_shared_from_this<SceneUnitModule>
	{
		friend SceneUnit;
	public:
		SceneUnitModule(ESceneUnitModule module_name) { m_module_name = module_name; };
		virtual ~SceneUnitModule();

		SceneUnit * GetOwner() { return m_owner; }
		NewScene * GetScene();
		inline ESceneUnitModule GetModuleName() { return m_module_name; }
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
		template <typename T>
		std::shared_ptr<T> GetModule()
		{
			return m_owner->GetModule<T>();
		}

		virtual uint64_t GetId();
		virtual void SetId(uint64_t val) {}
		inline SceneUnitEventProxy * GetEvProxy() { return m_event_proxy; }
		inline EventDispacherProxy * GetSceneEvProxy() { return m_scene_event_proxy; }

	protected:
		SceneUnit *m_owner = nullptr;
		ESceneUnitModule m_module_name = ESceneUnitModule_Count;
		EventDispacherProxy *m_scene_event_proxy = nullptr;
		SceneUnitEventProxy *m_event_proxy = nullptr;

	private:
		void Init(SceneUnit *owner);
		void Awake() { this->OnAwake(); }
		void Start() { this->OnStart(); }
		void Update() { this->OnUpdate(); }
		void Realse() { this->OnRelease(); }
		void Destroy();

	protected:
		virtual void OnInit() {}
		virtual void OnAwake() {}
		virtual void OnStart() {}
		virtual void OnUpdate() {}
		virtual void OnRelease() {}
		virtual void OnDestroy() {}
		virtual std::vector<SyncClientMsg> CollectPBInit() { return std::move(std::vector<SyncClientMsg>()); }
		virtual std::vector<SyncClientMsg> CollectPbMutable() { return std::move(std::vector<SyncClientMsg>()); }
		virtual void SetPbDirty() { m_pb_dirty = true; }
		virtual void ClearPbDirty() { m_pb_dirty = false; }
		virtual bool IsPbDirty() { return m_pb_dirty; }
		bool m_pb_dirty = false;

	public:
		void SendSelf(int protocol_id, google::protobuf::Message *msg);
		void SendSelfEx(std::vector<SyncClientMsg> msgs);
		void SendObservers(int protocol_id, google::protobuf::Message *msg);
		void SendObserversEx(std::vector<SyncClientMsg> msgs);
	};
}