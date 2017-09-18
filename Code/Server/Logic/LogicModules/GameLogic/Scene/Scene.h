#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include <google/protobuf/arena.h>

class GameLogicModule;

namespace GameLogic
{
	class Player;
	class SceneObject;
	class Hero;

	class Scene
	{
	public:
		Scene(GameLogicModule *logic_module);
		virtual ~Scene();
		bool Awake(void *param);
		void Update(long long now_ms);

		std::shared_ptr<Hero> GetRedHero() { return m_red_hero; }
		std::shared_ptr<Hero> GetBlueHero() { return m_blue_hero; }
	protected:
		GameLogicModule *m_logic_module = nullptr;;
		std::shared_ptr<Hero> m_red_hero;
		std::shared_ptr<Hero> m_blue_hero;
		uint64_t m_last_scene_objid = 0;
		std::unordered_map<uint64_t, std::shared_ptr<SceneObject>> m_scene_objs;
		google::protobuf::Arena *m_protobuf_arena = nullptr;

	public:
		static const uint64_t INVALID_SCENE_OBJID = 0;
		int64_t AddObject(std::shared_ptr<SceneObject> scene_obj);
		void RemoveObject(int64_t objid);
		
	protected:
		std::unordered_map<uint64_t, std::weak_ptr<SceneObject>> m_scene_objs_cache;
		std::unordered_set<uint64_t> m_removed_scene_objids;
		void CheckSceneObjectsCache();

	public:
		void PullAllSceneInfo(Player *player);
	};
}
