using Config;
using System;
using UnityEngine;

namespace Tool.Skill
{
    public abstract class EffectEditorBase
    {
        public const int EFFECT_CONFIG_ID_GAP = 100 * 10000; // 100WµÄ¼ä¸ô

        public EffectEditorBase(EffectTabData _tabData)
        {
            tabData = _tabData;
        }

        public EffectTabData tabData = null;

        public abstract void ImplEditorLogic();

        public abstract void LoadCfgs();

        public abstract bool SaveCfgs();

        public abstract ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn);

        public abstract EffectConfigBase GetCfg(int cfgId);
    }
}