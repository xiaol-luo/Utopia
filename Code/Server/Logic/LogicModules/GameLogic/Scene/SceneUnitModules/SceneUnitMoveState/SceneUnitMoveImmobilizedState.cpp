#include "SceneUnitMoveImmobilizedState.h"
#include "Common/Geometry/Vector3.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "Common/Macro/AllMacro.h"
#include "CommonModules/Log/LogModule.h"
#include "ServerLogics/ServerLogic.h"

GameLogic::SceneUnitMoveImmobilizedState::SceneUnitMoveImmobilizedState(SceneUnitMove *move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_Immobilized)
{
	m_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, m_move_agent->GetOwner()->GetScene()));
}

GameLogic::SceneUnitMoveImmobilizedState::~SceneUnitMoveImmobilizedState()
{

}

void GameLogic::SceneUnitMoveImmobilizedState::Enter(void * param)
{
	G_Log->Debug(LogModule::LOGGER_ID_STDOUT, "SceneUnitMoveImmobilizedState::Enter");
	m_is_done = false;
	m_ticker.RestartWithEndTimestamp(m_end_timestamp_ms * 0.001);
	m_is_done = !m_ticker.InCd();
	m_move_agent->GetNavAgent()->StopMove();
	m_move_agent->GetNavAgent()->Enable();
	m_move_agent->SetVelocity(Vector3::zero);
}

void GameLogic::SceneUnitMoveImmobilizedState::Exit()
{
	m_is_done = true;
	m_ticker.Restart(0);
}

void GameLogic::SceneUnitMoveImmobilizedState::Update(int64_t deltaMs)
{
	if (m_is_done)
		return;

	m_is_done = !m_ticker.InCd();
}

bool GameLogic::SceneUnitMoveImmobilizedState::IsDone()
{
	return m_is_done;
}

void GameLogic::SceneUnitMoveImmobilizedState::ImmobilizeEndMs(int64_t end_ms)
{
	m_end_timestamp_ms = end_ms;
}



