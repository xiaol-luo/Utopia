#pragma once

#include <stdint.h>
#include <google/protobuf/message.h>

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
		ESceneUnitModule_Move,
		ESceneUnitModule_Body,
		ESceneUnitModule_Sight,

		ESceneUnitModule_Count
	};

	const static uint64_t SCENE_UNIT_INVALID_ID = 0;

	struct SyncClientMsg
	{
		SyncClientMsg(int id, google::protobuf::Message *_msg) : protocol_id(id), msg(_msg) {}
		int protocol_id;
		google::protobuf::Message *msg;
	};
}