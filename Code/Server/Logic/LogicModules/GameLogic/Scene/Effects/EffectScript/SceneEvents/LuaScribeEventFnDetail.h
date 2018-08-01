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

	template <typename ...Args>
	void LuaScribeEventFnDetail_FireFnHelp(LuaSubcribeEventRecord *record, sol::table *self, Args... args)
	{
		LuaSubcribeEventRecord::Item *item = record->head->next;
		while (item != record->head)
		{
			item->fn(*self, args...);
			item = item->next;
		}
	}
	/// sol_ignore
	class LuaScribeEventFnDetail
	{
	public:
		virtual int GetEventId() = 0;
		virtual FnDoSubscribeEvent GetSubscribeEventFn() = 0;
	};

#define LuaScribeSceneUnitEventFnDetail_ClassBody \
public: \
	virtual int GetEventId() override; \
	virtual FnDoSubscribeEvent GetSubscribeEventFn() override;

#define LuaScribeSceneEventFnDetail_ClassBody \
public: \
	virtual int GetEventId() override; \
	virtual std::string GetLuaFunName() override; \
	virtual FnDoSubscribeEvent GetSubscribeEventFn() override;
}