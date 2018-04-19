#pragma once

namespace GameLogic
{
	class EffectConfigBase;
	class EffectScriptConfig;

}

namespace LuaDyCast
{
	GameLogic::EffectScriptConfig * ToEffectScriptConfig(GameLogic::EffectConfigBase *ptr);
}