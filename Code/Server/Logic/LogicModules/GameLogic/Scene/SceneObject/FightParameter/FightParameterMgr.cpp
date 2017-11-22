#include "FightParameterMgr.h"
#include "FightParameter.h"
#include <string>
#include <functional>
#include "GameLogic/Scene/SceneObject/FightUnit.h"

namespace GameLogic
{

	FightParameter * DefaultFightParameter(NetProto::EFightParam efp, int min_value, int min_base_value, int min_extra_value, int min_add_percent, int max_add_percent)
	{
		FightParameter *fp = new FightParameter();
		fp->SetFightParam(efp);
		fp->SetMinValue(min_value);
		fp->SetMaxValue(INT32_MAX);

		fp->SetBaseValueCalStrategy(NumUtil::ECS_Overlay);
		fp->SetBaseValueMin(min_base_value, false);
		fp->SetBaseValueMax(INT32_MAX, false);

		fp->SetExtraPercentCalStrategy(NumUtil::ECS_Overlay, false);
		fp->SetExtraPercentMin(min_add_percent, false);
		fp->SetExtraPercentMax(max_add_percent, false);

		fp->SetExtraValueCalStrategy(NumUtil::ECS_Overlay, false);
		fp->SetExtraValueMin(min_extra_value, false);
		fp->SetExtraValueMax(INT32_MAX, false);

		fp->Recal();
		return fp;
	}

	FightParameterMgr::FightParameterMgr(FightUnit * fight_unit)
	{
		m_fight_unit = fight_unit;
		memset(m_params, 0, sizeof(m_params));

		// 下面是属性值，一般来讲base_value>=0 value >= 0，其他的不作限制
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_MaxHP, 1, 1, 0, 0, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_MaxMP, 1, 1, 0, 0, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_MoveSpeed, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			// 算毫秒，最小攻击间隔250毫秒，百分比做倒数
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_AttackSpeed, 250, 0, INT_MIN, INT_MIN, INT_MAX); 
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetPercentAsDenominator(true);
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_AttackDist, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_PhyAttack, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_MagicAttack, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_PhyHurt, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_MagicHurt, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_PhyDefense, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_MagicDefense, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}

		// 下面的是状态 限制base_value为0， 由extra_value来控制状态起效
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_Dizziness, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(0);
			fp->SetBaseValueMin(0);
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_Silence, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(0);
			fp->SetBaseValueMin(0);
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_Blind, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(0);
			fp->SetBaseValueMin(0);
		}
		{
			FightParameter *fp = DefaultFightParameter(NetProto::EFP_Immobilized, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(0);
			fp->SetBaseValueMin(0);
		}

		// 设置初始值
		{
			m_params[NetProto::EFP_MaxHP]->AddBaseValue(1000);
			m_params[NetProto::EFP_MaxMP]->AddBaseValue(1000);
			m_params[NetProto::EFP_MoveSpeed]->AddBaseValue(12);
			m_params[NetProto::EFP_AttackDist]->AddBaseValue(2000); // 攻击间隔初始为2秒每次
			m_params[NetProto::EFP_AttackDist]->AddBaseValue(6);
			m_params[NetProto::EFP_PhyAttack]->AddBaseValue(10);
			m_params[NetProto::EFP_MagicAttack]->AddBaseValue(10);
			m_params[NetProto::EFP_PhyDefense]->AddBaseValue(10);
			m_params[NetProto::EFP_MagicDefense]->AddBaseValue(10);
		}

		auto value_change_cb = std::bind(&FightParameterMgr::OnValueChange, this, 
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		for (int i = 0; i < NetProto::EFP_COUNT; ++i)
		{
			if (nullptr != m_params[i])
			{
				m_params[i]->SetValueChangeCallback(value_change_cb);
			}
		}
	}

	FightParameterMgr::~FightParameterMgr()
	{
		for (int i = 0; i < sizeof(m_params) / sizeof(m_params[0]); ++i)
		{
			if (nullptr != m_params[i])
			{
				delete m_params[i];
				m_params[i] = nullptr;
			}
		}
	}

	FightParameter * FightParameterMgr::GetFightParam(NetProto::EFightParam efp)
	{
		return m_params[efp];
	}

	void FightParameterMgr::AddBaseValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		this->GetFightParam(efp)->AddBaseValue(val, recal, unique_id);
	}

	void FightParameterMgr::RemoveBaseValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		this->GetFightParam(efp)->RemoveBaseValue(val, recal, unique_id);
	}

	void FightParameterMgr::AddExtraPercent(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		this->GetFightParam(efp)->AddExtraPercent(val, recal, unique_id);
	}

	void FightParameterMgr::RemoveExtraPercent(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		this->GetFightParam(efp)->RemoveExtraPercent(val, recal, unique_id);
	}

	void FightParameterMgr::AddExtraValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		this->GetFightParam(efp)->AddExtraValue(val, recal, unique_id);
	}

	void FightParameterMgr::RemoveExtraValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		this->GetFightParam(efp)->RemoveExtraValue(val, recal, unique_id);
	}

	void FightParameterMgr::Recal(NetProto::EFightParam efp)
	{
		this->GetFightParam(efp)->Recal();
	}

	int FightParameterMgr::GetValue(NetProto::EFightParam efp, bool recal)
	{
		return this->GetFightParam(efp)->GetValue(recal);
	}

	void FightParameterMgr::OnValueChange(NetProto::EFightParam efp, int new_value, int old_value)
	{
		m_fpvc_events.push(FightParamValueChangeEvent(efp, new_value, old_value));

		switch (efp)
		{
		case NetProto::EFP_None:
			break;
		case NetProto::EFP_MaxHP:
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

		// trigger event
		--m_fpvc_call_semaphore;
		if (m_fpvc_call_semaphore >= 0)
		{
			while (!m_fpvc_events.empty())
			{
				FightParamValueChangeEvent event = m_fpvc_events.front();
				m_fpvc_events.pop();
				m_fight_unit->OnFightParamValueChange(event.efp, event.new_value, event.old_value);
			}
		}
		else
		{
			m_fpvc_events.pop();
			// log error
		}
		++m_fpvc_call_semaphore;
		
	}
}