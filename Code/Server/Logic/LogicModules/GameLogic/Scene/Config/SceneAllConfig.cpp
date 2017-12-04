#include "SceneAllConfig.h"
#include "SkillConfig.h"

GameLogic::SceneAllConfig::SceneAllConfig()
{
	skill_cfgs = new SkillConfigSet();
}

GameLogic::SceneAllConfig::~SceneAllConfig()
{
	delete skill_cfgs; skill_cfgs = nullptr;
}
