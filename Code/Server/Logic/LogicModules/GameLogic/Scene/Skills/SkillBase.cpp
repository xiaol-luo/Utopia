#include "SkillBase.h"
#include "SkillConfig.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/NewScene.h"
#include "Common/Utils/NumUtils.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitFightParam.h"
#include "Network/Protobuf/BattleEnum.pb.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Network/Protobuf/PID.pb.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/Effects/EffectBase.h"
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"
#include "Common/Geometry/GeometryUtils.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"

namespace GameLogic
{
	SkillBase::SkillBase(const SkillConfigBase * cfg)
	{
		m_cfg_base = cfg;
		assert(m_cfg_base);
	}

	SkillBase::~SkillBase()
	{

	}

	std::shared_ptr<SceneUnit> SkillBase::GetCaster()
	{
		return m_su_skills->GetOwner()->shared_from_this();
	}

	int64_t SkillBase::GetLogicMs(int64_t delta_ms)
	{
		int64_t ret = m_su_skills->GetOwner()->GetScene()->GetLogicMs() + delta_ms;
		return ret;
	}
}

