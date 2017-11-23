#include "SceneUnitModule.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"

namespace GameLogic
{
	uint64_t GameLogic::SceneUnitModule::GetId()
	{
		if (nullptr == m_owner)
			return 0;
		return m_owner->GetId();
	}
}


