#include "MoveMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneObject/MoveObject.h"
#include "Common/Utils/TimerUtil.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"
#include "Common/Utils/LogUtil.h"

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

	for (auto kv_pair : m_nav_agents)
	{
		kv_pair.second->OnMoved();
	}
}

void GameLogic::MoveMgr::OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs[move_obj->GetId()] = move_obj;
	++m_last_nav_agent_id;
	if (NavAgent::INVALID_ID == m_last_nav_agent_id)
		m_last_nav_agent_id = 1;
	NavAgent *nav_agent = new NavAgent(m_nav_mesh, m_last_nav_agent_id);
	m_nav_agents[nav_agent->GetId()] = nav_agent;
	move_obj->SetNavAgentId(nav_agent->GetId());
	nav_agent->SetPos(move_obj->GetPosition());
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
	nav_agent->SetAgentParams(params);
	auto xxx = std::bind(&GameLogic::MoveMgr::OnNavAgentMoved, this, std::placeholders::_1, move_obj);
	nav_agent->SetMovedCb(xxx);
	nav_agent->Enable();
}

void GameLogic::MoveMgr::OnNavAgentMoved(NavAgent *agent, std::weak_ptr<MoveObject> weak_move_obj)
{
	auto move_obj = weak_move_obj.lock();
	if (nullptr == move_obj)
	{
		LogUtil::Error(LogUtil::STDOUT, "MoveMgr::OnNavAgentMoved move object expired");
		return;
	}

	move_obj->setPosition(agent->GetPos());
	Vector3 pos = move_obj->GetPosition();
	LogUtil::Debug(LogUtil::STDOUT, "MoveMgr::OnNavAgentMoved id {0}, pos {1} {2} {3}", 
		move_obj->GetId(), pos.x, pos.y, pos.z);
}

void GameLogic::MoveMgr::OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs.erase(move_obj->GetId());
	auto it = m_nav_agents.find(move_obj->GetNavAgentId());
	move_obj->SetNavAgentId(NavAgent::INVALID_ID);
	if (m_nav_agents.end() != it)
	{
		delete it->second;
		m_nav_agents.erase(it);
	}
}

