#include "EffectForceMoveConfig.h"
#include "EffectForceMove.h"
#include "Config/AutoCsvCode/effect/CsvEffectForceMoveConfig.h"
#include <assert.h>
#include "GameLogic/Scene/Defines/EffectDefine.h"
#include "Utils/ConvertibleValue.h"

namespace GameLogic
{
	std::shared_ptr<EffectBase> EffectForceMoveConfig::CreateEffect(SceneEffects *scene_effects, uint64_t effect_key) const
	{
		return std::make_shared<EffectForceMove>(this, scene_effects, effect_key);
	}

	bool EffectForceMoveConfig::InitCfg(const Config::CsvEffectForceMoveConfig * csv_cfg)
	{
		m_id = csv_cfg->id;
		m_reversible = false;
		m_ignoreTerrian = csv_cfg->ignore_terrian;
		m_dir = csv_cfg->dir;
		m_anchor = StrToEffectFilterAnchor(csv_cfg->anchor);

		{
			int timeMs = 0;
			float speed = 0;
			float distance = 0;
			ConvertibleValue cv(csv_cfg->result, ';');
			assert(cv.ValueCount() >= 3);
			std::string flag = cv.GetStr(0);
			bool isOk = true;
			bool tmpOk = false;
			// 备注：t时间毫秒 d距离 s速度。知道任意2个可以推导出第三个。
			if ("ts" == flag) 
			{
				timeMs = cv.GetInt(1, &tmpOk); isOk &= tmpOk;
				speed = cv.GetFloat(2, &tmpOk); isOk &= tmpOk;
				assert(timeMs > 0 && speed > 0);
			}
			else if ("td" == flag)
			{
				timeMs = cv.GetInt(1, &tmpOk); isOk &= tmpOk;
				distance = cv.GetFloat(2, &tmpOk); isOk &= tmpOk;
				assert(timeMs > 0 && distance > 0);
				speed = distance / timeMs;
			}
			else if ("sd" == flag)
			{
				speed = cv.GetFloat(1, &tmpOk); isOk &= tmpOk;
				distance = cv.GetFloat(2, &tmpOk); isOk &= tmpOk;
				assert(speed > 0 && distance > 0);
				timeMs = distance / speed;
			}
			assert(isOk && timeMs > 0 && speed > 0);
		}
		return true;
	}
}

