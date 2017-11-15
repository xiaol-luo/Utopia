#pragma once

namespace NumUtil
{
	template <typename T>
	T GetInRange(T num, T min_val, T max_val)
	{
		if (min_val > max_val)
		{
			T tmp = min_val;
			min_val = max_val;
			max_val = tmp;
		}
		if (num < min_val)
			return min_val;
		if (num > max_val)
			return max_val;
		return num;
	}

	template <typename T>
	void MakeInAscOrder(T &v1, T &v2)
	{
		if (v1 > v2)
		{
			T tmp = v1;
			v1 = v2;
			v2 = tmp;
		}
	}
};
