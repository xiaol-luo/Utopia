#include "SceneHeroAction.h"
#include "GameLogic/AI/types/behaviac_types.h"
#include "behaviac/behaviac.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneModule/SceneNavMesh/SceneNavMesh.h"
#include "GameLogic/Scene/Navigation/NavMesh.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/Skills/Skill.h"
#include "Common/Geometry/GeometryUtils.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"

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
		m_move_param.check_span.SetTimeFunc(std::bind(&NewScene::GetLogicSec, m_owner->GetScene()));
	}

	void SceneHeroAction::OnUpdate()
	{
		behaviac::EBTStatus status = behaviac::BT_RUNNING;
		status = m_bt_agent->btexec();
		this->ProcessMove();
		this->ProcessUseSkill();
	}

	void SceneHeroAction::OnDestroy()
	{
		behaviac::Agent::Destroy(m_bt_agent);
		m_bt_agent = nullptr;
	}

	bool SceneHeroAction::Trace(uint64_t suid, float allow_distance)
	{
		std::shared_ptr<SceneUnitMove> su_move = m_owner->GetModule<SceneUnitMove>();
		if (nullptr == su_move)
			return false;

		this->CancelSkill();

		NewScene *scene = m_owner->GetScene();
		std::shared_ptr<SceneUnit> target_su = scene->GetUnit(suid);
		if (nullptr == target_su)
			return false;

		NavMesh *nav_mesh = scene->GetModule<SceneNavMesh>()->GetNavMesh();
		Vector3 fit_pos = su_move->GetPos();
		dtPolyRef poly_ref;
		if (!nav_mesh->FindNearestPoint(target_su->GetTransform()->GetPos(), poly_ref, fit_pos))
			nav_mesh->Raycast(su_move->GetPos(), target_su->GetTransform()->GetPos(), fit_pos);
		
		m_move_param.Reset();
		m_move_param.allow_distance = allow_distance;
		m_move_param.target_suid = suid;
		m_move_param.target_su = target_su;
		m_move_param.target_pos = fit_pos;
		m_move_param.try_moving = true;
		su_move->TryMoveToPos(m_move_param.target_pos);
		return true;
	}

	bool SceneHeroAction::MoveTo(Vector3 pos, float allow_distance)
	{
		std::shared_ptr<SceneUnitMove> su_move = m_owner->GetModule<SceneUnitMove>();
		if (nullptr == su_move)
			return false;

		this->CancelSkill();

		NewScene *scene = m_owner->GetScene();
		NavMesh *nav_mesh = scene->GetModule<SceneNavMesh>()->GetNavMesh();
		Vector3 fit_pos = m_owner->GetTransform()->GetPos();
		dtPolyRef poly_ref;
		if (!nav_mesh->FindNearestPoint(pos, poly_ref, fit_pos))
			return false;

		m_move_param.Reset();
		m_move_param.allow_distance = allow_distance;
		m_move_param.target_pos = fit_pos;
		m_move_param.try_moving = true;
		su_move->TryMoveToPos(m_move_param.target_pos);
		return true;
	}

	void SceneHeroAction::CancelMove()
	{
		m_move_param.Reset();

		std::shared_ptr<SceneUnitMove> su_move = m_owner->GetModule<SceneUnitMove>();
		if (nullptr == su_move)
			return;
		su_move->CancelMove();
	}

	bool SceneHeroAction::UseSkill(int skill_id, uint64_t su_id, Vector2 _pos, float _dir)
	{
		if (!CancelSkill())
			return false;

		Vector3 pos = Vector3(_pos.x, 0, _pos.y);
		m_using_skill = nullptr;
		std::shared_ptr<SceneUnitSkills> su_skills = m_owner->GetModule<SceneUnitSkills>();
		if (nullptr == su_skills)
			return false;
		std::shared_ptr<Skill> skill = su_skills->GetActiveSkill(skill_id);
		if (nullptr == skill)
			return false;

		Vector3 locate_pos = m_owner->GetTransform()->GetPos();
		Vector2 dir = (pos - locate_pos).xz();
		dir.normalize();
		skill->SetParams(su_id, pos, dir);
		bool ret = skill->Begin();
		if (ret)
		{
			m_using_skill = skill;
		}
		return ret;
	}

	bool SceneHeroAction::CancelSkill()
	{
		bool ret = false;
		if (ret || nullptr == m_using_skill)
			ret = true;
		if (ret || ! m_using_skill->IsRunning())
			ret = true;
		if (ret || m_using_skill->TryCancel())
			ret = true;
		if (ret)
		{
			m_using_skill = nullptr;
		}
		return ret;
	}

	void SceneHeroAction::ProcessMove()
	{
		if (!m_move_param.try_moving)
			return;


		if (m_move_param.first_check || !m_move_param.check_span.InCd())
		{
			m_move_param.first_check = false;
			m_move_param.check_span.Restart(0.2f);

			if (0 == m_move_param.target_suid)
			{
				if (GeometryUtils::InFlatDistance(m_owner->GetTransform()->GetPos(), m_move_param.target_pos, m_move_param.allow_distance))
					this->CancelMove();
			}
			else
			{
				auto target_su = m_move_param.target_su.lock();
				if (nullptr == target_su)
				{
					this->CancelMove();
				}
				else
				{
					std::shared_ptr<SceneUnitMove> su_move = m_owner->GetModule<SceneUnitMove>();
					if (nullptr == su_move)
					{
						this->CancelMove();
					}
					else
					{
						m_move_param.target_pos = target_su->GetTransform()->GetPos();
						if (GeometryUtils::InFlatDistance(m_owner->GetTransform()->GetPos(), m_move_param.target_pos, m_move_param.allow_distance))
						{
							su_move->CancelMove();
						}
						else
						{
							su_move->TryMoveToPos(m_move_param.target_pos);
						}
					}
				}
			}
		}
	}

	void SceneHeroAction::ProcessUseSkill()
	{
		if (nullptr != m_using_skill)
		{
			m_using_skill->HeartBeat();
		}
	}

	std::vector<SyncClientMsg> SceneHeroAction::CollectPBInit()
	{
		std::vector<SyncClientMsg> msgs;
		if (nullptr != m_using_skill)
		{
			msgs.push_back(m_using_skill->GetPbMsg());
		}
		return std::move(msgs);
	}
}