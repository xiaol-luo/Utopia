#include "SceneAllConfig.h"
#include "GameLogic/Scene/Skills/SkillConfig.h"
#include "GameLogic/Scene/Effects/EffectConfigMgr.h"
#include "GameLogic/Scene/Effects/EffectFilterConfig.h"

GameLogic::SceneAllConfig::SceneAllConfig()
{
	skill_cfgs = new SkillConfigSet();
	effect_cfg_mgr = new EffectConfigMgr();
	effect_filter_cfg_mgr = new EffectFilterConfigMgr();
}

GameLogic::SceneAllConfig::~SceneAllConfig()
{
	delete skill_cfgs; skill_cfgs = nullptr;
	delete effect_cfg_mgr; effect_cfg_mgr = nullptr;
	delete effect_filter_cfg_mgr; effect_filter_cfg_mgr = nullptr;
}
