#include "LuaDynamicCasts.h"
#include "GameLogic/Scene/Effects/EffectConfigBase.h"
#include "GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"

GameLogic::EffectScriptConfig * LuaDyCast::ToEffectScriptConfig(GameLogic::EffectConfigBase * ptr)
{
	return dynamic_cast<GameLogic::EffectScriptConfig *>(ptr);
}
