#pragma once

#include <stdint.h>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "GameLogic/Scene/Defines/SceneDefine.h"
#include "GameLogic/Scene/Defines/ViewDefine.h"
#include "Common/Define/NetworkDefine.h"
#include "Common/Geometry/Vector3.h"
#include "Network/Protobuf/BattleEnum.pb.h"

class EventDispacher;

namespace Config
{
	struct CsvSceneConfig;
}

class GameLogicModule;

namespace GameLogic
{
	class Player;
	class SceneModule;
	class SceneUnit;
	struct SceneAllConfig;

	class NewScene
	{
	public:
		NewScene(GameLogicModule *logic_module);
		virtual ~NewScene();

		void AddModule(SceneModule *module);
		bool Awake();
		void Update();
		void Destroy();
	protected:
		virtual bool OnAwake() { return true; }
		virtual bool OnLateAwake() { return true; }
		virtual void OnUpdate() {}
		virtual void OnLateUpdate() {}
		virtual void OnDestroy() {}
		virtual void OnLateDestroy() {}

	public:
		float GetLogicSec();
		inline int64_t GetLogicMs() { return m_logic_ms; }
		inline int64_t GetLogicDetalMs() { return m_logic_detal_ms; }
		inline EventDispacher * GetEvDispacher() { return m_ev_dispacher; }
	protected:
		bool m_is_pause = false;
		int64_t m_logic_ms = 0;
		int64_t m_logic_detal_ms = 0;
		int64_t m_last_real_ms = 0;
		EventDispacher *m_ev_dispacher;

	public:
		template <typename T>
		T * GetModule()
		{
			T *ptr = nullptr;
			int idx = T::MODULE_TYPE;
			if (idx >= 0 && idx < ESceneModule_Count)
				ptr = dynamic_cast<T *>(m_modules[idx]);
			return ptr;
		}
		GameLogicModule * GetGameLogic() { return m_game_logic; }
		const SceneAllConfig * GetCfg() { return m_cfg; }
	protected:
		GameLogicModule *m_game_logic;
		bool m_awaked = false;
		bool m_started = false;
		SceneModule *m_modules[ESceneModule_Count];
		SceneAllConfig *m_cfg = nullptr;

	public:
		uint64_t AddUnit(std::shared_ptr<SceneUnit> su);
		void RemoveUnit(uint64_t id);
		std::shared_ptr<SceneUnit> GetUnit(uint64_t id);

	protected:
		uint64_t m_last_scene_unit_id;
		std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> m_scene_units;
		std::unordered_map<uint64_t, std::weak_ptr<SceneUnit>> m_cached_scene_units;
		std::unordered_set<uint64_t> m_removed_scene_unit_ids;
		std::unordered_set<uint64_t> m_new_scene_unit_ids;
		void UpdateCachedSceneUnits();

	protected:
		void TestEvent(int ev_id, std::shared_ptr<SceneUnit> su);
		void TestSubscribeEvents();

	public:
		bool PlayerSelectHero(Player *player, uint64_t su_id);
		void OnPlayerDisconnect(Player *player);
		void OnPlayerQuit(Player *player);
		void SetPlayerViewCamp(Player *player, EViewCamp view_camp);
		void SendPlayer(NetId netid, int protocol_id, google::protobuf::Message *msg);
		void SendPlayer(NetId netid, const std::vector<SyncClientMsg> &msgs);
		void SendObservers(int64_t su_id, int protocol_id, google::protobuf::Message *msg);
		void SendObservers(int64_t su_id, const std::vector<SyncClientMsg> &msgs);
		void SendViewCamp(EViewCamp view_camp, int protocol_id, google::protobuf::Message *msg, bool to_ob=true);
		void SendViewCamp(EViewCamp view_camp, const std::vector<SyncClientMsg> &msgs, bool to_ob=true);
		std::unordered_map<NetId, Player *> m_player_view_camps[EViewCamp_Observer + 1];
		template <typename T>
		T * CreateProtobuf()
		{
			return google::protobuf::Arena::CreateMessage<T>(m_protobuf_arena);
		}
	protected:
		google::protobuf::Arena *m_protobuf_arena = nullptr;

	public:
		void MakeSnapshot(bool syncClient);
	protected:
		struct ViewCampDiff
		{
			void Clear() 
			{
				more_sus.clear(); miss_su_ids.clear(); 
				more_gird_ids.clear(); miss_su_ids.clear();
			}

			std::unordered_map<uint64_t, std::weak_ptr<SceneUnit>> more_sus;
			std::unordered_set<uint64_t> miss_su_ids;
			std::unordered_set<int> more_gird_ids;
			std::unordered_set<int> miss_grid_ids;
		};
		ViewCampDiff m_view_camp_diff[EViewCamp_Observer];

	public:
		// msg logic
		std::shared_ptr<SceneUnit> red_su = nullptr;
		std::shared_ptr<SceneUnit> blue_su = nullptr;

	public:
		NetProto::ESkillEffectCase SceneUnitRelation(std::shared_ptr<SceneUnit> one, std::shared_ptr<SceneUnit> another);
	};
}
