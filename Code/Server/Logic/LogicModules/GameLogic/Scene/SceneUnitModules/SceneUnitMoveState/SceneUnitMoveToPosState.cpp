#include "SceneUnitMoveToPosState.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Geometry/Vector3.h"
#include "Common/Geometry/Vector2.h"
#include "Common/Macro/AllMacro.h"
#include "ServerLogics/ServerLogic.h"
#include "CommonModules/Log/LogModule.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"

GameLogic::SceneUnitMoveToPosState::SceneUnitMoveToPosState(SceneUnitMove * move_agent) : SceneUnitMoveState(move_agent, NetProto::EMoveAgentState_MoveToPos)
{

}

GameLogic::SceneUnitMoveToPosState::~SceneUnitMoveToPosState()
{

}

void GameLogic::SceneUnitMoveToPosState::Enter(void * param)
{
	Vector3 from = m_move_agent->GetPos();
	G_Log->Debug(LogModule::LOGGER_ID_STDOUT, 
		"SceneUnitMoveToPosState::Enter: from{:3.2f}, {:3.2f}, {:3.2f} to {:3.2f}, {:3.2f}, {:3.2f} #",
		from.x, from.y, from.z,
		m_desired_pos.x, m_desired_pos.y, m_desired_pos.z);
	m_move_agent->SetVelocity(Vector3::zero);
	NavAgent *agent = m_move_agent->GetNavAgent();
	agent->SetPos(m_move_agent->GetPos());
	agent->TryMoveToPos(m_desired_pos);
	agent->Enable();
}

void GameLogic::SceneUnitMoveToPosState::Exit()
{
	m_move_agent->GetNavAgent()->StopMove();
}

void GameLogic::SceneUnitMoveToPosState::Update(int64_t deltaMs)
{
	m_move_agent->GetNavAgent()->OnMoved();
}

void GameLogic::SceneUnitMoveToPosState::Flash(const Vector3 & val)
{
	m_move_agent->GetNavAgent()->SetPos(val);
}

bool GameLogic::SceneUnitMoveToPosState::IsDone()
{
	bool ret = (m_desired_pos.XZ() - m_move_agent->GetPos().XZ()).SqrMagnitude() < MOVE_TO_POS_IGNORE_SQR_DISTANCE;
	return ret;
}

void GameLogic::SceneUnitMoveToPosState::SetDesiredPos(const Vector3 &pos)
{
	m_desired_pos = pos;
}

void GameLogic::SceneUnitMoveToPosState::CollectMoveDetail(NetProto::SceneUnitMove * msg)
{
	::NetProto::PBVector2* pos = msg->mutable_move_desired_pos();
	pos->set_x(m_desired_pos.x);
	pos->set_y(m_desired_pos.z);
	msg->set_max_move_speed(m_move_agent->GetNavAgent()->GetMaxSpeed());
}

