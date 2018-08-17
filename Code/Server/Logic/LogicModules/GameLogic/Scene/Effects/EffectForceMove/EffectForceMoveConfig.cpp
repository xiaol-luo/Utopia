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

	bool EffectForceMoveConfig::InitCfg(const Config::CsvEffectForceMoveConfig * csv_cfg, void **param)
	{
		sol::table json_cfg = *(sol::table *)param;
		if (json_cfg.valid())
		{
			m_id = json_cfg["id"];
			m_name = json_cfg["name"];


			m_ignoreTerrian = json_cfg["ignore_terrian"];
			m_moveDeg = json_cfg["angle"];
			m_anchor = json_cfg["anchor"];

			MoveSetting move_setting = json_cfg["move_setting"];
			float move_sec = json_cfg["move_sec"];
			float move_speed = json_cfg["move_speed"];
			float move_distance = json_cfg["move_distance"];
			switch (move_setting)
			{
			case TimeSpeed:
			{
				m_timeSec = move_sec;
				m_speed = move_speed;
			}
			break;
			case TimeDistance:
			{
				m_timeSec = move_sec;
				assert(fabs(m_timeSec) > FLT_EPSILON);
				m_speed = move_distance / m_timeSec;
			}
			break;
			case DistanceSpeed:
			{
				m_speed = move_speed;
				assert(fabs(m_speed) > FLT_EPSILON);
				m_timeSec = move_distance / m_speed;
			}
			break;
			default:
				break;
			}
			assert(fabs(m_timeSec) > FLT_EPSILON);
			assert(fabs(m_speed) > FLT_EPSILON);
		}
		else if (nullptr != csv_cfg)
		{
			m_id = csv_cfg->id;
			m_reversible = false;
			m_ignoreTerrian = csv_cfg->ignore_terrian;
			m_moveDeg = csv_cfg->angle;
			m_anchor = StrToForceMoveAnchor(csv_cfg->anchor);

			{
				int timeSec = 0;
				float speed = 0;
				float distance = 0;
				ConvertibleValue cv(csv_cfg->result, ';');
				assert(cv.ValueCount() >= 3);
				std::string flag = cv.GetStr(0);
				bool isOk = true;
				bool tmpOk = false;
				// 备注：t时间毫秒 s速度 d距离。知道任意2个可以推导出第三个。
				if ("ts" == flag)
				{
					timeSec = cv.GetInt(1, &tmpOk); isOk &= tmpOk;
					speed = cv.GetFloat(2, &tmpOk); isOk &= tmpOk;
					assert(timeSec > 0 && speed > 0);
				}
				else if ("td" == flag)
				{
					timeSec = cv.GetInt(1, &tmpOk); isOk &= tmpOk;
					distance = cv.GetFloat(2, &tmpOk); isOk &= tmpOk;
					assert(timeSec > 0 && distance > 0);
					speed = distance / timeSec;
				}
				else if ("sd" == flag)
				{
					speed = cv.GetFloat(1, &tmpOk); isOk &= tmpOk;
					distance = cv.GetFloat(2, &tmpOk); isOk &= tmpOk;
					assert(speed > 0 && distance > 0);
					timeSec = distance / speed;
				}
				assert(isOk && timeSec > 0 && speed > 0);
				m_timeSec = timeSec;
				m_speed = speed;
			}
		}

		return true;
	}
}

