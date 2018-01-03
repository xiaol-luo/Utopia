#pragma once

namespace Config
{
	struct CsvSceneConfig;
}

namespace GameLogic
{
	class EffectFilterConfigMgr;
	class EffectConfigMgr;
	struct SkillConfigSet;

	struct SceneAllConfig
	{
		SceneAllConfig();
		~SceneAllConfig();

		Config::CsvSceneConfig *scene_cfg = nullptr;
		SkillConfigSet *skill_cfgs = nullptr;
		EffectConfigMgr *effect_cfg_mgr = nullptr;
		EffectFilterConfigMgr *effect_filter_cfg_mgr = nullptr;
	};
}
