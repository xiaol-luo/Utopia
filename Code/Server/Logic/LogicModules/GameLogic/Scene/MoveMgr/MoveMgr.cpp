#include "MoveMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneObject/MoveObject.h"
#include "Common/Utils/TimerUtil.h"

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
}

void GameLogic::MoveMgr::OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs[move_obj->GetId()] = move_obj;
}

void GameLogic::MoveMgr::OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs.erase(move_obj->GetId());
}

