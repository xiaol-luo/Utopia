#include "SceneAllConfig.h"
#include "GameLogic/Scene/Skills/SkillConfig.h"
#include "GameLogic/Scene/Effects/EffectConfigMgr.h"

GameLogic::SceneAllConfig::SceneAllConfig()
{
	skill_cfgs = new SkillConfigSet();
	effect_cfg_mgr = new EffectConfigMgr();
}

GameLogic::SceneAllConfig::~SceneAllConfig()
{
	delete skill_cfgs; skill_cfgs = nullptr;
	delete effect_cfg_mgr; effect_cfg_mgr = nullptr;
}
