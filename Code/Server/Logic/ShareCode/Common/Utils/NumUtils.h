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

	const int BIT_PER_BYTE = 8;
	template <typename Ret, typename T, typename K>
	Ret MakeUnionValue(T t, K k)
	{
		Ret ret = (Ret)t << (sizeof(k) * BIT_PER_BYTE) | k;
	}


	enum ECalculateStrategy
	{
		ECS_Overlay = 0,		// 叠加
		ECS_MaxPriority,		// 最大优先
		ECS_MinPriority,		// 最小优先

		ECS_Count,
	};

	template <typename K, typename V>
	class FightParameterValue
	{
		std::vector<V> m_values;
		struct UniqueValue
		{
			std::vector<V> values;
		};

		std::map<K, UniqueValue> m_unique_values;
		ECalculateStrategy m_cal_strategy = ECS_Overlay;


		V m_value = 0;
		V m_min_value = 0;
		V m_max_value = 0;

		void RemoveElem(std::vector<V> &vec, V val)
		{
			int idx = -1;
			for (int i = 0; i < (int)vec.size(); ++i)
			{
				if (val == vec[i])
				{
					idx = i;
					break;
				}
			}
			if (idx >= 0)
				vec.erase(vec.begin() + idx);
		}

	public:
		void Init(V min_value, V max_value, ECalculateStrategy cal_strategy)
		{
			this->Reset();
			m_min_value = min_value;
			m_max_value = max_value;
			m_cal_strategy = cal_strategy;
		}

		void Reset()
		{
			m_unique_values.clear();
			m_values.clear();
			m_value = 0;
		}

		void Add(V val, K unique_id, bool is_recal=true)
		{
			if (0 == unique_id)
			{
				m_values.push_back(val);
			}
			else
			{
				auto it = m_unique_values.find(unique_id);
				if (m_unique_values.end() == it)
				{
					auto ret = m_unique_values.insert(std::make_pair(unique_id, UniqueValue()));
					if (ret.second)
						it = ret.first;
				}
				if (m_unique_values.end() != it)
				{
					UniqueValue &unique_value = it->second;
					unique_value.values.push_back(val);
				}
			}
			if (is_recal)
				this->Recalcute();
		}

		void Remove(V val, K unique_id, bool is_recal=true)
		{
			if (0 == unique_id)
			{
				this->RemoveElem(m_values, val);
			}
			else
			{
				auto it = m_unique_values.find(unique_id);
				if (m_unique_values.end() != it)
				{
					UniqueValue &unique_value = it->second;
					RemoveElem(unique_value.values, val);
					if (unique_value.values.empty())
						m_unique_values.erase(it);
				}
			}
			if (is_recal)
				this->Recalcute();
		}

		V GetValue()
		{
			return m_value;
		}

		void SetMinValue(V val, bool is_recal=true)
		{
			m_min_value = val;
			NumUtil::MakeInAscOrder(m_min_value, m_max_value);
			if (is_recal)
				this->Recalcute();
		}

		void SetMaxValue(V val, bool is_recal=true)
		{
			m_max_value = val;

			NumUtil::MakeInAscOrder(m_min_value, m_max_value);
			if (is_recal)
				this->Recalcute();
		}

		void SetCalculateStrategy(ECalculateStrategy cs, bool is_recal=true)
		{
			m_cal_strategy = cs;
			if (is_recal)
				this->Recalcute();
		}

		void Recalcute()
		{
			m_value = 0;

			if (m_cal_strategy == ECS_Overlay)
			{
				for (int val : m_values)
					m_value += val;
				for (auto &&kvPair : m_unique_values)
				{
					UniqueValue &unique_value = kvPair.second;
					m_value += *std::max_element(unique_value.values.begin(), unique_value.values.end());
				}
			}
			m_value = NumUtil::GetInRange(m_value, m_min_value, m_max_value);
		}
	};
};
