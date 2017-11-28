#include "Ticker.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Timer/ITimerModule.h"

float NowSecond()
{
	return GlobalServerLogic->GetTimerModule()->NowMs() *1.0f / ITimerModule::MS_PER_SEC;
}


Ticker::Ticker()
{
	m_now_sec_func = std::bind(NowSecond);
	this->Restart(0);
}

Ticker::~Ticker()
{

}

void Ticker::SetTimeFunc(std::function<float()> func)
{
	m_now_sec_func = func;
	this->Restart(0);
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

float Ticker::EndTimestamp()
{
	return m_start + m_cd;
}

bool Ticker::InCd()
{
	return this->LeftTime() > FLT_EPSILON;
}

