#include <string>
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"
#include "ShareCode/Network/Protobuf/Battle.pb.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/NewScene.h"

namespace GameLogic
{
	typedef bool(*FnSubscribeSceneEventHelp)(LuaSubcribeEventRecord*, sol::table *self, EventDispacherProxy*, int);

	// sol_ignore
	class LuaScribeSceneEventFnDetail
	{
	public:
		virtual int GetEventId() = 0;
		virtual std::string GetLuaFunName() = 0;
		virtual FnSubscribeSceneEventHelp GetSubscribeEventFn() = 0;

		static std::vector<LuaScribeSceneEventFnDetail *> s_allFnDetails;
	};

#define LuaScribeSceneEventFnDetail_ClassBody \
public: \
	virtual int GetEventId() override; \
	virtual std::string GetLuaFunName() override; \
	virtual FnSubscribeSceneEventHelp GetSubscribeEventFn() override;

	// sol_ignore
	class LuaScribeSceneEventFnDetail_OnSceneUnitFightParamChange : public LuaScribeSceneEventFnDetail  { LuaScribeSceneEventFnDetail_ClassBody; };
}