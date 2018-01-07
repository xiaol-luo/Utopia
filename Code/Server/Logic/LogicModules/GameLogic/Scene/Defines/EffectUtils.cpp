#include "EffectUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace GameLogic
{
	bool EffectUtil::UnitCanBeHurt(std::shared_ptr<SceneUnit> su)
	{
		std::shared_ptr<SceneUnitFightParam> su_fp = su->GetModule<SceneUnitFightParam>();
		if (nullptr == su_fp)
			return false;
		if (su_fp->GetHp() <= 0)
			return false;
		return true;
	}
	bool EffectUtil::UnitIsAlive(std::shared_ptr<SceneUnit> su)
	{
		std::shared_ptr<SceneUnitFightParam> su_fp = su->GetModule<SceneUnitFightParam>();
		if (nullptr == su_fp)
			return false;
		if (su_fp->GetHp() <= 0)
			return false;
		return true;
	}
}
