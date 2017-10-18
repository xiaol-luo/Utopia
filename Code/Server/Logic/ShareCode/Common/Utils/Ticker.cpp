#include "Ticker.h"
#include "TimerUtil.h"

float NowSecond()
{
	return TimerUtil::NowMs() * 1.0f / ITimerModule::MS_PER_SEC;
}

Ticker::Ticker(std::function<long()> m_now_sec_func)
{
	m_now_sec_func = m_now_sec_func;
	this->Restart(0);
}

Ticker::Ticker()
{
	m_now_sec_func = std::bind(NowSecond);
	this->Restart(0);
}

Ticker::~Ticker()
{
}

void Ticker::Restart()
{
	this->Restart(m_cd);
}

void Ticker::Restart(float newCd)
{
	m_start = m_now_sec_func();
	m_cd = newCd;
}

float Ticker::LeftTime()
{
	float left_time = m_start + m_cd - m_now_sec_func();
	return left_time < FLT_EPSILON ? 0 : left_time;
}

float Ticker::ElaspeTime()
{
	return m_now_sec_func() - m_start;
}

bool Ticker::InCd()
{
	return this->LeftTime() > FLT_EPSILON;
}
