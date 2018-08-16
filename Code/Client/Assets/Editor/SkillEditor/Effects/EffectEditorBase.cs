using Config;
using System;
using UnityEngine;

namespace Tool.Skill
{
    public class EffectEditorBase
    {
        public const int EFFECT_CONFIG_ID_GAP = 100 * 10000; // 100WµÄ¼ä¸ô

        public EffectEditorBase(EffectTabData _tabData)
        {
            tabData = _tabData;
        }

        public EffectTabData tabData = null;

        public virtual void ImplEditorLogic()
        {
            GUILayout.Label("look here");
        }

        public virtual void LoadCfgs()
        {

        }

        public virtual bool SaveCfgs()
        {
            return false;
        }

        public virtual ConfigIdNameListStruct GetCfgIdNameList(Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = new ConfigIdNameListStruct();
            return ret;
        }
    }
}