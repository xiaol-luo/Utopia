#pragma once

#include <functional>

class Ticker
{
public:
	Ticker();
	~Ticker();

	void SetTimeFunc(std::function<float()> func);
	void Restart();
	void Restart(float newCd);
	void RestartWithEndTimestamp(float end_time);
	float SetCd(float val) { m_cd = val; }
	float GetCd() { return m_cd; }
	float GetStart() { return m_start; }
	float LeftTime();
	float ElaspeTime();
	float EndTimestamp();
	bool InCd();

private:
	std::function<float()> m_now_sec_func = nullptr;
	float m_start; // second
	float m_cd; // second
};
