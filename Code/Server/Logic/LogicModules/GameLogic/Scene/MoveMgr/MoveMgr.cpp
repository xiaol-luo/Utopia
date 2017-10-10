#include "MoveMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMgr.h"
#include "GameLogic/Scene/Scene.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneObject/MoveObject.h"

GameLogic::MoveMgr::MoveMgr(Scene * scene) : m_scene(scene)
{
	m_navMgr = new NavMgr();
}

GameLogic::MoveMgr::~MoveMgr()
{
	delete m_navMgr; m_navMgr = nullptr;
}

bool GameLogic::MoveMgr::Awake()
{
	bool ret = m_navMgr->Init(m_scene->NavMesh());
	return ret;
}

void GameLogic::MoveMgr::Update()
{
	m_navMgr->Update();
}

void GameLogic::MoveMgr::OnMoveObjectEnterScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs[move_obj->GetId()] = move_obj;
}

void GameLogic::MoveMgr::OnMoveObjectLeaveScene(std::shared_ptr<MoveObject> move_obj)
{
	m_move_objs.erase(move_obj->GetId());
}

