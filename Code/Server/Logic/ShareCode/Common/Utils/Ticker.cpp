#include "Ticker.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Timer/ITimerModule.h"

float NowSecond()
{
	return GlobalServerLogic->GetTimerModule()->NowMs() *1.0f / ITimerModule::MS_PER_SEC;
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

void Ticker::RestartWithEndTimestamp(float end_time)
{
	m_start = m_now_sec_func();
	m_cd = end_time - m_start;
	if (m_cd < FLT_EPSILON)
		m_cd = 0;
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

