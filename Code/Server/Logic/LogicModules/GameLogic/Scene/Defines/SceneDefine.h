#pragma once

#include <stdint.h>
#include <google/protobuf/message.h>
#include "GameLogic/Scene/Defines/ViewDefine.h"

namespace GameLogic
{
	enum ESceneObjectShape
	{
		ESceneObjectShape_Circle = 0,
	};

	enum ESceneModule
	{
		ESceneModule_NavMesh = 0,
		ESceneModule_Move,
		ESceneModule_View,

		ESceneModule_Count,
	};

	enum ESceneUnitModule
	{
		ESceneUnitModule_Transform = 0,
		ESceneUnitModule_FightParam,
		ESceneUnitModule_Move,
		ESceneUnitModule_Body,
		ESceneUnitModule_Sight,
		ESceneUnitModule_Action,
		ESceneUnitModule_Skills,

		ESceneUnitModule_Count
	};

	const static uint64_t SCENE_UNIT_INVALID_ID = 0;

	struct SyncClientMsg
	{
		SyncClientMsg(int id, google::protobuf::Message *_msg) : protocol_id(id), msg(_msg) {}
		int protocol_id;
		google::protobuf::Message *msg;
	};

	const static float MOVE_TO_POS_IGNORE_DISTANCE = 0.42f; // 移动时，距离目标点为N算到达
	const static float MOVE_TO_POS_IGNORE_SQR_DISTANCE = MOVE_TO_POS_IGNORE_DISTANCE * MOVE_TO_POS_IGNORE_DISTANCE;		

	enum ESUAction
	{
		ESUAction_Idle = 0,
		ESUAction_Move,
		ESUAction_Trace,
		ESUAction_UseSkill,
	};

	enum ESUFaceDir
	{
		ESUFaceDir_Move = 0,
		ESUFaceDir_Skill,

		ESUFaceDir_Count,
	};
}