#pragma once
#include <stdint.h>
#include <assert.h>

template <typename T, int LenDescriptSize>
struct StreamLenPraser
{
	const static int LEN_DESCRIPT_SIZE = LenDescriptSize;
	static_assert(LenDescriptSize > 0, "LenDescriptSize should greater than 0");

	static T Prase(char *data, uint32_t data_len)
	{
		if (data_len < LEN_DESCRIPT_SIZE)
			return T(0);

		T val = *(T *)data;
		return val;
	}
};

template <typename T, int LenDescriptSize>
struct NetSteamLenPraser
{
	const static int LEN_DESCRIPT_SIZE = LenDescriptSize;
	static_assert(LenDescriptSize > 0, "LenDescriptSize should greater than 0");

	static T Prase(char *data, uint32_t data_len)
	{
		if (data_len < LEN_DESCRIPT_SIZE)
			return T(0);
		if (LEN_DESCRIPT_SIZE <= sizeof(uint16_t))
			return T(ntohs(*(T*)data));
		if (LEN_DESCRIPT_SIZE <= sizeof(uint32_t))
			return T(ntohl(*(T*)data));
		if (LEN_DESCRIPT_SIZE <= sizeof(uint64_t))
			return T(ntohll(*(T*)data));
		assert(false);
		return T(0);
	}
};

template <typename T, typename LenParseType=StreamLenPraser<T, sizeof(T)>>
class UseLenPraser
{
public:
	bool ParseNext(char *data, uint32_t data_len)
	{
		if (data_len < LenParseType::LEN_DESCRIPT_SIZE)
			return false;

		T len = LenParseType::Prase(data, data_len);
		return true;
	}
};

