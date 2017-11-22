#include "FightUnit.h"
#include "FightParameter/FightParameterMgr.h"
#include "Common/Utils/NumUtils.h"

namespace GameLogic
{
	FightUnit::FightUnit(ESceneObjectType obj_type) : MoveObject(obj_type)
	{
		m_fight_param_mgr = new FightParameterMgr(this);
	}

	FightUnit::~FightUnit()
	{
		delete m_fight_param_mgr;
	}

	void FightUnit::OnEnterScene(Scene * scene)
	{
		MoveObject::OnEnterScene(scene);
	}

	void FightUnit::OnLeaveScene(Scene * scene)
	{
		MoveObject::OnLeaveScene(scene);
	}

	void FightUnit::Update(long long now_ms)
	{
		MoveObject::Update(now_ms);

		m_fight_param_mgr->AddBaseValue(NetProto::EFP_MaxHP, 1, true);
		m_fight_param_mgr->AddExtraPercent(NetProto::EFP_MaxHP, 1, true);
		m_fight_param_mgr->AddExtraValue(NetProto::EFP_MaxHP, 1, true);
	}

	void FightUnit::OnFightParamValueChange(NetProto::EFightParam efp, int new_value, int old_value)
	{
		switch (efp)
		{
		case NetProto::EFP_None:
			break;
		case NetProto::EFP_MaxHP:
			this->OnMaxHpChange(new_value, old_value);
			break;
		case NetProto::EFP_MaxMP:
			break;
		case NetProto::EFP_MoveSpeed:
			break;
		case NetProto::EFP_AttackDist:
			break;
		case NetProto::EFP_AttackSpeed:
			break;
		case NetProto::EFP_Dizziness:
			break;
		case NetProto::EFP_Silence:
			break;
		case NetProto::EFP_Blind:
			break;
		case NetProto::EFP_Immobilized:
			break;
		case NetProto::EFP_PhyAttack:
			break;
		case NetProto::EFP_MagicAttack:
			break;
		case NetProto::EFP_PhyHurt:
			break;
		case NetProto::EFP_MagicHurt:
			break;
		case NetProto::EFP_PhyDefense:
			break;
		case NetProto::EFP_MagicDefense:
			break;
		case NetProto::EFP_COUNT:
			break;
		case NetProto::EFightParam_INT_MIN_SENTINEL_DO_NOT_USE_:
			break;
		case NetProto::EFightParam_INT_MAX_SENTINEL_DO_NOT_USE_:
			break;
		default:
			break;
		}
	}
	void FightUnit::OnMaxHpChange(int new_value, int old_value)
	{
		if (this->IsAlive())
		{
			int delta_val = new_value - old_value;
			if (delta_val > 0)
				m_hp += delta_val;
		}
		NumUtil::GetInRange(m_hp, 0, new_value);
	}

	bool FightUnit::IsAlive()
	{
		return m_hp > 0;
	}
}