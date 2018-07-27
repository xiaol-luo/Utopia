#include "LuaSubscribeEventDetail.h"
#include "Common/EventDispatcher/EventDispacher.h"
#include "Common/EventDispatcher/EventDispacherProxy.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "Utils/LuaUtils.h"

namespace GameLogic
{
	LuaSubscribeSceneEventDetail::LuaSubscribeSceneEventDetail(EffectScript * effect, EventDispacher * ev_proxy)
	{
		m_effect = effect;
		m_ev_proxy = new EventDispacherProxy(ev_proxy);
	}

	LuaSubscribeSceneEventDetail::~LuaSubscribeSceneEventDetail()
	{
		this->ClearAll();
		m_effect = nullptr;
		delete m_ev_proxy; m_ev_proxy = nullptr;
	}
	void LuaSubscribeSceneEventDetail::Remove(uint64_t record_item_id)
	{

	}
	void LuaSubscribeSceneEventDetail::ClearAll()
	{

	}
}