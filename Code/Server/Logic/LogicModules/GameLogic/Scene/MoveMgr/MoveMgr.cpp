#include "MoveMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneObject/MoveObject.h"
#include "Common/Utils/TimerUtil.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Utils/LogUtil.h"
#include "GameLogic/Scene/MoveMgr/MoveAgent.h"

GameLogic::MoveMgr::MoveMgr(Scene * scene) : m_scene(scene)
{
	m_nav_mesh = scene->NavMesh();
}

GameLogic::MoveMgr::~MoveMgr()
{

}

bool GameLogic::MoveMgr::Awake()
{
	return true;
}

void GameLogic::MoveMgr::Update()
{
	long deltaMs = TimerUtil::DeltaMs();
	m_nav_mesh->GetCrowd()->update(deltaMs * 0.001, nullptr);

	for (auto kv_pair : m_move_agents)
	{
		kv_pair.second->Update(deltaMs);
	}
}

void GameLogic::MoveMgr::TryMoveToPos(uint64_t agent_id, const Vector3 &pos)
{
	NavAgent *agent = this->GetNavAgent(agent_id);
	if (nullptr != agent)
		agent->TryMoveToPos(pos);
}

void GameLogic::MoveMgr::TryMoveToDir(uint64_t agent_id, float angle)
{
	NavAgent *agent = this->GetNavAgent(agent_id);
	if (nullptr != agent)
		agent->TryMoveToDir(angle);
}

void GameLogic::MoveMgr::StopMove(uint64_t agent_id)
{
	NavAgent *agent = this->GetNavAgent(agent_id);
	if (nullptr != agent)
		agent->StopMove();
}

void GameLogic::MoveMgr::TryResumeMove(uint64_t agent_id)
{
	NavAgent *agent = this->GetNavAgent(agent_id);
	if (nullptr != agent)
		agent->TryResumeMove();
}

GameLogic::NavAgent * GameLogic::MoveMgr::GetNavAgent(uint64_t agent_id)
{
	auto it = m_move_agents.find(agent_id);
	if (m_move_agents.end() != it)
		return it->second->GetNavAgent();
	return nullptr;
}

void GameLogic::MoveMgr::SetMaxSpeed(uint64_t agent_id, float max_speed)
{
	NavAgent *agent = this->GetNavAgent(agent_id);
	if (nullptr != agent)
		agent->SetMaxSpeed(max_speed);
}

void GameLogic::MoveMgr::OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs[move_obj->GetId()] = move_obj;
	++m_last_move_agent_id;
	if (MoveAgent::INVALID_ID == m_last_move_agent_id)
		m_last_move_agent_id = 1;
	MoveAgent *move_agent = new MoveAgent(this);
	move_agent->SetId(m_last_move_agent_id);
	move_obj->SetMoveAgent(move_agent);
	m_move_agents[move_agent->GetId()] = move_agent;
	{
		NavAgent *nav_agent = move_agent->GetNavAgent();
		dtCrowdAgentParams params;
		memset(&params, 0, sizeof(params));
		params.radius = move_obj->GetRadius();
		params.height = move_obj->GetHeight();
		params.maxAcceleration = 32 * 40;
		params.maxSpeed = move_obj->GetSpeed();
		params.collisionQueryRange = params.radius * 12.0f;
		params.pathOptimizationRange = params.radius * 30.0f;
		params.separationWeight = 0;
		params.updateFlags = 0;
		params.updateFlags |= DT_CROWD_ANTICIPATE_TURNS;
		params.updateFlags |= DT_CROWD_OPTIMIZE_VIS;
		params.updateFlags |= DT_CROWD_OPTIMIZE_TOPO;
		//params.updateFlags |= DT_CROWD_OBSTACLE_AVOIDANCE;
		if (params.separationWeight > 0.001f) params.updateFlags |= DT_CROWD_SEPARATION;
		params.obstacleAvoidanceType = 3;
		// params.avoidancePriority = 0.5f; 
		params.queryFilterType = 0;
		nav_agent->SetPos(move_obj->GetPosition());
		nav_agent->SetAgentParams(params);
		nav_agent->Enable();
	}
	{
		move_agent->SetPos(move_obj->GetPosition());
		move_agent->SetMoveMaxSpeed(move_obj->GetSpeed());
		MoveAgent::EventCallback event_cb;
		event_cb.move_state_cb = std::bind(&GameLogic::MoveObject::OnMoveStateChange, move_obj, std::placeholders::_1, std::placeholders::_2);
		event_cb.velocity_change_cb = std::bind(&GameLogic::MoveObject::OnVelocityChange, move_obj, std::placeholders::_1, std::placeholders::_2);
		event_cb.post_change_cb = std::bind(&GameLogic::MoveObject::OnPostChange, move_obj, std::placeholders::_1, std::placeholders::_2);
		move_agent->SetEventCb(event_cb);
	}
}

void GameLogic::MoveMgr::OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs.erase(move_obj->GetId());
	auto it = m_move_agents.find(move_obj->GetMoveAgent()->GetId());
	move_obj->SetMoveAgent(nullptr);
	if (m_move_agents.end() != it)
	{
		delete it->second;
		m_move_agents.erase(it);
	}
}

