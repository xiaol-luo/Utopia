#pragma once

#include <sol.hpp>
#include "ConfigUtil.h"

class ConvertibleValue
{
	template <typename T>
	struct ParseResultItem
	{
		bool isOk = false;
		T val = T();
	};

	template <typename T>
	struct ParseResult
	{
		using ResultItemType = ParseResultItem<T>;

		bool isParsed = false;
		std::vector<ResultItemType > result;

		void Reset()
		{
			isParsed = false;
			result.clear();
		}
	};

public:
	ConvertibleValue(const std::string &str, char sep);
	void SetSep(char sep);
	uint32_t ValueCount();
	std::string GetStr(uint32_t idx = 0, bool *isOk = nullptr);
	int GetInt(uint32_t idx = 0, bool *isOk = nullptr);
	int64_t GetInt64(uint32_t idx = 0, bool *isOk = nullptr);
	uint32_t GetUint32(uint32_t idx = 0, bool *isOk = nullptr);
	uint64_t GetUint64(uint32_t idx = 0, bool *isOk = nullptr);
	float GetFloat(uint32_t idx = 0, bool *isOk = nullptr);
	double GetDouble(uint32_t idx = 0, bool *isOk = nullptr);

protected:
	char m_sep = ' ';
	std::string m_str;
	ParseResult<std::string> m_strs;
	ParseResult<int> m_ints;
	ParseResult<int64_t> m_int64s;
	ParseResult<uint32_t> m_uints;
	ParseResult<uint64_t> m_uint64s;
	ParseResult<float> m_floats;
	ParseResult<double> m_doubles;

	void DoSplitStr();

	template <typename T>
	T GetVal(ParseResult<T> &parseRet, uint32_t idx, bool *isOk)
	{
		if (idx >= this->ValueCount())
		{
			if (nullptr != isOk) *isOk = false;
			return 0;
		}
		if (!parseRet.isParsed)
		{
			parseRet.Reset();
			parseRet.isParsed = true;
			for (auto strItem : m_strs.result)
			{
				ParseResult<T>::ResultItemType item;
				std::string str = strItem.val;
				item.isOk = ConfigUtil::Str2BaseValue(str, (T &)item.val);
				parseRet.result.push_back(item);
			}
		}
		if (nullptr != isOk) *isOk = parseRet.result[idx].isOk;
		return parseRet.result[idx].val;
	}
};


