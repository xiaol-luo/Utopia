#include "SceneUnitFightParam.h"
// #include "Common/Utils/TupleUtil.h"
#include "GameLogic/Scene/Defines/SceneEventID.h"
#include "GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"
#include <assert.h>

namespace GameLogic
{
	SceneUnitFightParam::SceneUnitFightParam() : SceneUnitModule(MODULE_TYPE)
	{
		memset(m_params, 0, sizeof(m_params));
		memset(m_fix_params, 0, sizeof(m_fix_params));
	}

	SceneUnitFightParam::~SceneUnitFightParam()
	{

	}

	FightParam * SceneUnitFightParam::GetParam(NetProto::EFightParam efp)
	{
		if (efp < 0 || efp >= NetProto::EFP_COUNT)
			return nullptr;
		return m_params[efp];
	}
	FightParam * SceneUnitFightParam::GetParamFix(NetProto::EFightParam efp)
	{
		if (efp < 0 || efp >= NetProto::EFP_COUNT)
			return nullptr;
		return m_fix_params[efp];
	}
	void SceneUnitFightParam::AddBaseValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_params[efp])
			return;
		m_params[efp]->AddBaseValue(val, recal, unique_id);

	}
	void SceneUnitFightParam::RemoveBaseValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_params[efp])
			return;
		m_params[efp]->RemoveBaseValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::AddBaseValueFix(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return;
		m_fix_params[efp]->AddBaseValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::RemoveBaseValueFix(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return;
		m_fix_params[efp]->RemoveBaseValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::AddExtraPercent(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_params[efp])
			return;
		m_params[efp]->AddExtraPercent(val, recal, unique_id);
	}
	void SceneUnitFightParam::RemoveExtraPercent(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_params[efp])
			return;
		m_params[efp]->RemoveExtraPercent(val, recal, unique_id);
	}
	void SceneUnitFightParam::AddExtraPercentFix(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return;
		m_fix_params[efp]->AddExtraPercent(val, recal, unique_id);
	}
	void SceneUnitFightParam::RemoveExtraPercentFix(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return;
		m_fix_params[efp]->RemoveExtraPercent(val, recal, unique_id);
	}
	void SceneUnitFightParam::AddExtraValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_params[efp])
			return;
		m_params[efp]->AddExtraValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::RemoveExtraValue(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_params[efp])
			return;
		m_params[efp]->RemoveExtraValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::AddExtraValueFix(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return;
		m_fix_params[efp]->AddExtraValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::RemoveExtraValueFix(NetProto::EFightParam efp, int val, bool recal, int unique_id)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return;
		m_fix_params[efp]->RemoveExtraValue(val, recal, unique_id);
	}
	void SceneUnitFightParam::Recal(NetProto::EFightParam efp, bool include_fix)
	{
		if (efp < 0 || efp >= NetProto::EFP_COUNT)
			return;
		if (nullptr != m_params[efp])
			m_params[efp]->Recal();
		if (include_fix && NULL != m_fix_params[efp])
			m_fix_params[efp]->Recal();

	}
	int SceneUnitFightParam::GetValue(NetProto::EFightParam efp, bool include_fix)
	{
		int value = 0;
		if (efp < 0 || efp >= NetProto::EFP_COUNT)
			return 0;
		if (nullptr != m_params[efp])
			value += m_params[efp]->GetValue(true);
		if (include_fix && NULL != m_fix_params[efp])
			value += m_fix_params[efp]->GetValue(true);
		return value;
	}
	void SceneUnitFightParam::RecalFix(NetProto::EFightParam efp)
	{
		if (efp < 0 || efp >= NetProto::EFP_COUNT)
			return;
		if (nullptr != m_fix_params[efp])
			m_fix_params[efp]->Recal();
	}
	int SceneUnitFightParam::GetValueFix(NetProto::EFightParam efp, bool recal)
	{
		assert(this->HasFixParam(efp));

		if (efp < 0 || efp >= NetProto::EFP_COUNT || nullptr == m_fix_params[efp])
			return 0;
		return m_fix_params[efp]->GetValue(true);
	}

	void SceneUnitFightParam::AttachState(NetProto::EFightParam efp)
	{
		assert(this->IsState(efp));
		this->AddBaseValue(efp, 1);
	}

	void SceneUnitFightParam::DeattachState(NetProto::EFightParam efp)
	{
		assert(this->IsState(efp));
		this->RemoveBaseValue(efp, 1);
	}

	bool SceneUnitFightParam::IsStateActive(NetProto::EFightParam efp)
	{
		assert(this->IsState(efp));
		return this->GetValue(efp) > 0;
	}

	void SceneUnitFightParam::OnValueChange(bool is_fix, NetProto::EFightParam efp, int new_value, int old_value)
	{
		m_ev_queue.push(std::make_tuple(is_fix, efp, new_value, old_value));
		while (!m_ev_queue.empty() && !m_ev_firing)
		{
			auto t = m_ev_queue.front();
			m_ev_queue.pop();

			FireEventHelp(std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t));
		}
	}

	void SceneUnitFightParam::FireEventHelp(bool is_fix, NetProto::EFightParam efp, int new_value, int old_value)
	{
		m_ev_firing = true;
		this->CheckStateChange(is_fix, efp, new_value, old_value);
		this->GetEvProxy()->Fire(ESU_FightParamChange, is_fix, efp, new_value, old_value);
		m_ev_firing = false;
	}

	void SceneUnitFightParam::OnInit()
	{
		this->ForTestInitParam();
		this->ForTestInitFixParam();
	}

	void SceneUnitFightParam::OnDestroy()
	{
		for (int i = 0; i < NetProto::EFP_COUNT; ++i)
		{
			delete m_params[i]; m_params[i] = nullptr;
			delete m_fix_params[i]; m_fix_params[i] = nullptr;
		}
	}

	FightParam * DefaultFightParameter(NetProto::EFightParam efp, int min_value, int min_base_value, int min_extra_value, int min_add_percent, int max_add_percent)
	{
		FightParam *fp = new FightParam();
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

	void SceneUnitFightParam::ForTestInitParam()
	{
		memset(m_params, 0, sizeof(m_params));
		// 下面是属性值，一般来讲base_value> =0 value >= 0，其他的不作限制
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_MaxHP, 1, 1, 0, 0, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_MaxMP, 1, 1, 0, 0, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_MoveSpeed, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			// 算毫秒，最小攻击间隔250毫秒，百分比做倒数
			FightParam *fp = DefaultFightParameter(NetProto::EFP_AttackSpeed, 250, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetPercentAsDenominator(true);
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_AttackDist, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_PhyAttack, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_MagicAttack, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_PhyHurt, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_MagicHurt, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_PhyDefense, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_MagicDefense, 0, 0, INT_MIN, INT_MIN, INT_MAX);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
		}

		// 下面的是状态 限制base_value为0， 由extra_value来控制状态起效
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_Dizzy, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(INT_MAX);
			fp->SetBaseValueMin(0);
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_Silence, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(INT_MAX);
			fp->SetBaseValueMin(0);
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_Blind, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(INT_MAX);
			fp->SetBaseValueMin(0);
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_Dead, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(INT_MAX);
			fp->SetBaseValueMin(0);
		}
		{
			FightParam *fp = DefaultFightParameter(NetProto::EFP_Immobilized, 0, 0, 0, 0, 0);
			assert(nullptr == m_params[fp->GetFightParam()]);
			m_params[fp->GetFightParam()] = fp;
			fp->SetBaseValueMax(INT_MAX);
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

		auto value_change_cb = std::bind(&SceneUnitFightParam::OnValueChange, this, false,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		for (int i = 0; i < NetProto::EFP_COUNT; ++i)
		{
			if (nullptr != m_params[i])
			{
				m_params[i]->SetValueChangeCallback(value_change_cb);
			}
		}
	}
	void SceneUnitFightParam::ForTestInitFixParam()
	{
		auto value_change_cb = std::bind(&SceneUnitFightParam::OnValueChange, this, true,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		for (int i = 0; i < NetProto::EFP_COUNT; ++i)
		{
			if (nullptr != m_params[i])
			{
				m_fix_params[i] = DefaultFightParameter((NetProto::EFightParam)i, 0, 0, INT_MIN, INT_MIN, INT_MAX);
				m_fix_params[i]->SetValueChangeCallback(value_change_cb);
			}
		}
	}

	bool SceneUnitFightParam::HasParam(NetProto::EFightParam efp)
	{
		bool ret = true;
		switch (efp)
		{
		case NetProto::EFP_HP:
		case NetProto::EFP_MP:
			ret = false;
			break;
		}
		return ret;
	}

	bool SceneUnitFightParam::HasFixParam(NetProto::EFightParam efp)
	{
		bool ret = false;
		switch (efp)
		{
		case NetProto::EFP_MaxHP:
		case NetProto::EFP_MaxMP:
			ret = true;
			break;
		}
		return ret;
	}

	bool SceneUnitFightParam::IsState(NetProto::EFightParam efp)
	{
		bool ret = false;
		switch (efp)
		{
		case NetProto::EFP_Dizzy:
		case NetProto::EFP_Immobilized:
		case NetProto::EFP_Blind:
		case NetProto::EFP_Dead:
		case NetProto::EFP_Silence:
			ret = true;
			break;
		}
		return ret;
	}

	void SceneUnitFightParam::CheckStateChange(bool is_fix, NetProto::EFightParam efp, int new_value, int old_value)
	{
		if (is_fix || !this->IsState(efp))
			return;

		bool attach_state = old_value <= 0 && new_value > 0;
		bool deattach_state = old_value > 0 && new_value <= 0;
		if (!attach_state && !deattach_state)
			return;

		switch (efp)
		{
		case NetProto::EFP_Dizzy:
			this->GetEvProxy()->Fire(ESU_DizzinessChange, attach_state);
			break;
		case NetProto::EFP_Immobilized:
			this->GetEvProxy()->Fire(ESU_ImmobilizedChange, attach_state);
			break;
		case NetProto::EFP_Blind:
			this->GetEvProxy()->Fire(ESU_BlindChange, attach_state);
			break;
		case NetProto::EFP_Silence:
			this->GetEvProxy()->Fire(ESU_SilenceChange, attach_state);
			break;
		case NetProto::EFP_Dead:
			this->GetEvProxy()->Fire(ESU_DeadChange, attach_state);
			break;
		}
	}
	int SceneUnitFightParam::GetHp()
	{
		return m_hp;
	}
	int SceneUnitFightParam::AddHp(int delta, EffectBase *effect)
	{
		int old_hp = m_hp;
		m_hp += delta;
		m_hp = NumUtil::GetInRange(m_hp, 0, this->GetValue(NetProto::EFP_MaxHP));
		m_event_proxy->Fire(ES_HpChange, m_hp, old_hp, delta, effect);
		return m_hp;
	}
	int SceneUnitFightParam::GetMp()
	{
		return m_mp;
	}
	int SceneUnitFightParam::AddMp(int delta, EffectBase *effect)
	{
		int old_mp = m_mp;
		m_mp += delta;
		m_mp = NumUtil::GetInRange(m_mp, 0, this->GetValue(NetProto::EFP_MaxMP));
		m_event_proxy->Fire(ES_MpChange, m_mp, old_mp, delta, effect);
		return m_mp;
	}
}