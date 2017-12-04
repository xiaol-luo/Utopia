#pragma once

namespace Config
{
	struct CsvSceneConfig;
}

namespace GameLogic
{
	struct SkillConfigSet;
	struct SceneAllConfig
	{
		SceneAllConfig();
		~SceneAllConfig();

		Config::CsvSceneConfig *scene_cfg = nullptr;
		SkillConfigSet *skill_cfgs = nullptr;
	};
}
