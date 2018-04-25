#pragma once

#include <string>

namespace GameLogic
{
	class SkillConfigBase
	{
	public:
		~SkillConfigBase() {}
		int id = 0;
		std::string name;
	};
}