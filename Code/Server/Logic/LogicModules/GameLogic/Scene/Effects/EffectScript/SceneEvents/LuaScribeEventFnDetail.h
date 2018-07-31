#pragma once

#include <string>
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"
#include "ShareCode/Network/Protobuf/Battle.pb.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/NewScene.h"

namespace GameLogic
{
	typedef bool(*FnDoSubscribeEvent)(LuaSubcribeEventRecord*, sol::table *self, EventDispacherProxy*, int, void **);

	/// sol_ignore
	class LuaScribeEventFnDetail
	{
	public:
		virtual int GetEventId() = 0;
		virtual std::string GetLuaFunName() = 0;
		virtual FnDoSubscribeEvent GetSubscribeEventFn() = 0;
	};

#define LuaScribeSceneEventFnDetail_ClassBody \
public: \
	virtual int GetEventId() override; \
	virtual std::string GetLuaFunName() override; \
	virtual FnDoSubscribeEvent GetSubscribeEventFn() override;
}