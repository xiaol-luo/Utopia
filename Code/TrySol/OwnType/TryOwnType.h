#pragma once

#include <string>

namespace TryOwnType
{
	struct Head
	{
		float weight;
		int param_int;
	};

	struct Foot
	{
		float length;
		int param_int;
	};

	struct Human
	{
		std::string name;
		Head head;
		// Foot foot;
		// Head *head_ptr;
		// Foot *foot_ptr;
	};

	struct Student : public Human
	{
		int score;
	};

	struct Teacher : public Human
	{
		int work_age;
	};
}
