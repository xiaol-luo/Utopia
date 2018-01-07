#include "EffectAttrs.h"
#include <assert.h>
#include "EffectAttrsConfig.h"
#include "GameLogic/Scene/Defines/EffectUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"

namespace GameLogic
{
	EffectAttrs::EffectAttrs(const EffectConfigBase * cfg, SceneEffects * scene_effects, uint64_t effect_key)
		: EffectBase(cfg, scene_effects, effect_key)
	{
		m_cfg = dynamic_cast<const EffectAttrsConfig *>(cfg);
		assert(m_cfg);
	}

	EffectAttrs::~EffectAttrs()
	{

	}

	void EffectAttrs::OnBegin()
	{
		std::shared_ptr<SceneUnit> target_su = this->GetEffectTarget();
		if (nullptr != target_su && EffectUtil::UnitIsAlive(target_su))
		{
			std::shared_ptr<SceneUnitFightParam> su_fp = target_su->GetModule<SceneUnitFightParam>();
			if (nullptr != su_fp)
			{
				m_cfg->GetFightParamKvs().Attach(su_fp, true);
			}
		}

		if (!m_cfg->Reversible())
		{
			m_is_done = true;
		}
	}

	void EffectAttrs::OnLateEnd(EEffectEndCase end_case)
	{
		if (m_cfg->Reversible())
		{
			std::shared_ptr<SceneUnit> target_su = this->GetEffectTarget();
			if (nullptr != target_su && EffectUtil::UnitIsAlive(target_su))
			{
				std::shared_ptr<SceneUnitFightParam> su_fp = target_su->GetModule<SceneUnitFightParam>();
				if (nullptr != su_fp)
				{
					m_cfg->GetFightParamKvs().Deattach(su_fp, true);
				}
			}
		}
		m_is_done = true;
	}

	void EffectAttrs::OnLoop(int64_t now_ms, int64_t delta_ms)
	{
		if (now_ms - m_begin_ms >= m_cfg->GetHoldTime())
		{
			m_is_done = true;
		}
	}
}
