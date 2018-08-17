
using Config;
using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tool.Skill
{
    public class ConfigIdNameListStruct
    {
        public List<int> ids = new List<int>();
        public List<string> names = new List<string>();
    }

    public enum EffectType
    {
        Group,
        Seacher,
        Attrs,
        Hurt,
        Heal,
        ForceMove,
        
        Script_GuideMissile = 200,

        Count,
    }

    public class EffectTabData
    {
        public EffectTabData(SkillEditorWindowData _editorData)
        {
            editorData = _editorData;
            effectEditors[EffectType.Group] = new GroupEffectEditor(this);
            effectEditors[EffectType.Seacher] = new SearcherEffectEditor(this);
            effectEditors[EffectType.Attrs] = new AttrsEffectEditor(this);
            effectEditors[EffectType.Hurt] = new HurtEffectEditor(this);
            effectEditors[EffectType.Heal] = new HealEffectEditor(this);
            effectEditors[EffectType.ForceMove] = new ForceMoveEffectEditor(this);
            // effectEditors[EffectType.Script_GuideMissile] = new EffectEditorBase(this);
        }

        public SkillEditorWindowData editorData;

        public EffectType selectedEffectType;
        Dictionary<EffectType, EffectEditorBase> effectEditors = new Dictionary<EffectType, EffectEditorBase>();

        public EffectEditorBase GetEffectEditor(EffectType eType)
        {
            EffectEditorBase ret = null;
            effectEditors.TryGetValue(eType, out ret);
            return ret;
        }

        public void LoadCfgs()
        {
            foreach (var item in effectEditors.Values)
            {
                item.LoadCfgs();
            }
        }

        public void SaveCfgs()
        {
            foreach (var item in effectEditors.Values)
            {
                item.SaveCfgs();
            }
        }

        public ConfigIdNameListStruct GetCfgIdNameList(EffectType eType, Predicate<EffectConfigBase> filterFn)
        {
            ConfigIdNameListStruct ret = null;
            EffectEditorBase editor = this.GetEffectEditor(eType);
            if (null != editor)
            {
                ret = editor.GetCfgIdNameList(filterFn);
            }
            return null != ret ? ret : new ConfigIdNameListStruct();
        }

        public class EffectConfigDetail
        {
            public EffectType type = EffectType.Count;
            public EffectConfigBase cfg = null;
        }

        public EffectConfigDetail GetEffecCfg(int cfgId)
        {
            EffectConfigDetail ret = new EffectConfigDetail();
            foreach (var kvPair in effectEditors)
            {
                var cfg = kvPair.Value.GetCfg(cfgId);
                if (null != cfg)
                {
                    ret.type = kvPair.Key;
                    ret.cfg = cfg;
                    break;
                }
            }
            return ret;
        }

        public void ImplEditorLogic()
        {
            EffectEditorBase editor = this.GetEffectEditor(selectedEffectType);
            if (null != editor)
            {
                editor.ImplEditorLogic();
            }
        }
    }
}