#include "ConvertibleValue.h"

ConvertibleValue::ConvertibleValue(const std::string & str, char sep)
{
	m_str = str;
	ConfigUtil::Trim(m_str, std::set<char>({ ' ', '\t', '\r', '\n', m_sep }));
	this->SetSep(sep);
}

void ConvertibleValue::SetSep(char sep)
{
	m_sep = sep;
	m_strs.Reset();
	m_ints.Reset();
	m_uints.Reset();
	m_int64s.Reset();
	m_uint64s.Reset();
	m_floats.Reset();
	m_doubles.Reset();
}

uint32_t ConvertibleValue::ValueCount()
{
	DoSplitStr();
	return m_strs.result.size();
}

std::string ConvertibleValue::GetStr(uint32_t idx, bool * isOk)
{
	DoSplitStr();
	if (idx >= m_strs.result.size())
	{
		if (nullptr != isOk) *isOk = false;
		return std::move(std::string());
	}
	if (nullptr != isOk) *isOk = true;
	return m_strs.result[idx].val;
}

void ConvertibleValue::DoSplitStr()
{
	if (m_strs.isParsed)
		return;

	m_strs.isParsed = true;
	std::vector<std::string> strs = ConfigUtil::SplitStr(m_str, m_sep);
	for (auto str : strs)
	{
		ParseResult<std::string>::ResultItemType item;
		item.val = str;
		item.isOk = true;
		m_strs.result.push_back(item);
	}
}

int ConvertibleValue::GetInt(uint32_t idx, bool * isOk)
{
	auto val = GetVal(m_ints, idx, isOk);
	return val;
}

int64_t ConvertibleValue::GetInt64(uint32_t idx, bool * isOk)
{
	auto val = GetVal(m_int64s, idx, isOk);
	return val;
}

uint32_t ConvertibleValue::GetUint32(uint32_t idx, bool * isOk)
{
	auto val = GetVal(m_uints, idx, isOk);
	return val;
}

uint64_t ConvertibleValue::GetUint64(uint32_t idx /*= 0*/, bool *isOk /*= nullptr*/)
{
	auto val = GetVal(m_uint64s, idx, isOk);
	return val;
}

float ConvertibleValue::GetFloat(uint32_t idx, bool * isOk)
{
	auto val = GetVal(m_floats, idx, isOk);
	return val;
}

double ConvertibleValue::GetDouble(uint32_t idx, bool * isOk)
{
	auto val = GetVal(m_doubles, idx, isOk);
	return val;
}
