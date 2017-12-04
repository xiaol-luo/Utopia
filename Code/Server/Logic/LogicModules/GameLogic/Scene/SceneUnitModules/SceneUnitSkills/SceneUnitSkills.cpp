#include "SceneUnitSkills.h"

namespace GameLogic
{
	SceneUnitSkills::SceneUnitSkills() : SceneUnitModule(MODULE_TYPE)
	{
	}

	SceneUnitSkills::~SceneUnitSkills()
	{
		for (auto &slot_array : m_slots)
		{
			for (auto &slot : slot_array)
				slot = nullptr;
		}
	}
}
