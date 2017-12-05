#include "SceneHeroAction.h"
#include "GameLogic/AI/types/behaviac_types.h"
#include "behaviac/behaviac.h"

namespace GameLogic
{
	SceneHeroAction::SceneHeroAction() : SceneUnitModule(MODULE_TYPE)
	{

	}

	SceneHeroAction::~SceneHeroAction()
	{

	}

	void SceneHeroAction::OnAwake()
	{
		m_bt_agent = behaviac::Agent::Create<AIHero>();
		const char *bt_tree_name = "FirstBT";
		bool ret = m_bt_agent->btload(bt_tree_name);
		m_bt_agent->btsetcurrent(bt_tree_name);
		assert(ret);
	}

	void SceneHeroAction::OnUpdate()
	{
		behaviac::EBTStatus status = behaviac::BT_RUNNING;
		status = m_bt_agent->btexec();
	}

	void SceneHeroAction::OnDestroy()
	{
		behaviac::Agent::Destroy(m_bt_agent);
		m_bt_agent = nullptr;
	}
}