#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include <google/protobuf/arena.h>
#include "Common/Define/NetworkDefine.h"
#include "GameLogic/Scene/SceneObject/SceneObject.h"

class GameLogicModule;
class EventDispacher;

namespace Config
{
	struct CsvSceneConfig;
}

namespace GameLogic
{
	class Player;
	class SceneObject;
	class Hero;
	class NavMesh;
	class MoveMgr;
	class MoveObject;
	class ViewMgr;
	class SceneEventDispacher;
	class SceneUnit;

	class Scene
	{
	public:
		static const uint64_t INVALID_SCENE_OBJID = 0;

	public:
		Scene(GameLogicModule *logic_module);
		virtual ~Scene();
		bool Awake(void *param);
		void Update(long long now_ms);

	public: 
		inline MoveMgr * GetMoveMgr() { return m_move_mgr; }
		inline NavMesh * GetNavMesh() { return m_nav_mesh; }
		inline ViewMgr * GetViewMgr() { return m_view_mgr; }
		inline SceneEventDispacher * GetEventDispacher() { return m_event_dispacher; }
		inline long GetLogicMs() { return m_logic_ms; }
		inline long GetLogicDetalMs() { return m_logic_detal_ms; }
		inline EventDispacher * GetEvDispacher() { return m_ev_dispacher; }
	protected:
		bool m_is_pause = false;
		uint64_t m_logic_ms = 0;
		uint64_t m_logic_detal_ms = 0;
		uint64_t m_last_real_ms = 0;

		GameLogicModule *m_logic_module = nullptr;;
		NavMesh *m_nav_mesh = nullptr;
		MoveMgr *m_move_mgr = nullptr;
		ViewMgr *m_view_mgr = nullptr;
		SceneEventDispacher *m_event_dispacher = nullptr;
		Config::CsvSceneConfig *m_sceneCfg = nullptr;

	public:
		inline std::shared_ptr<Hero> GetRedHero() { return m_red_hero; }
		inline std::shared_ptr<Hero> GetBlueHero() { return m_blue_hero; }
		int64_t AddObject(std::shared_ptr<SceneObject> scene_obj);
		void RemoveObject(int64_t objid);
	protected:
		std::shared_ptr<Hero> m_red_hero;
		std::shared_ptr<Hero> m_blue_hero;
		uint64_t m_last_scene_objid = 0;
		std::unordered_map<uint64_t, std::shared_ptr<SceneObject>> m_scene_objs;
		google::protobuf::Arena *m_protobuf_arena = nullptr;
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> m_scene_objs_cache;
		std::unordered_set<uint64_t> m_removed_scene_objids;
		void CheckSceneObjectsCache();

	public:
		template <typename T> 
		T * CreateProtobuf()
		{
			return google::protobuf::Arena::CreateMessage<T>(m_protobuf_arena);
		}
		void SendClient(NetId netid, int protocol_id, google::protobuf::Message *msg);
		void SendClient(NetId netid, const std::vector<SyncClientMsg> &msgs);
		void SendViewCamp(EViewCamp view_camp, int protocol_id, google::protobuf::Message *msg);
		void SendViewCamp(EViewCamp view_camp, const std::vector<SyncClientMsg> &msgs);
		void PullAllSceneInfo(Player *player);
		void SyncAllSceneObjectState(Player *player, int filter_flag, bool include_unchanged);

	private:
		void HandleViewChange();
		EventDispacher *m_ev_dispacher;
	};
}
