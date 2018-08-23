using Config;
using Config.EffectScript;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEditor;

namespace Tool.Skill
{
    public partial class ScriptEffectEditor
    {
        void ImplBulletEditorLogic(EffectScriptConfig cfg, SkillEditorWindowData editorData)
        {
            var setting = JsonConvert.DeserializeObject<Config.EffectScript.BulletSetting>(cfg.json_param);
            if (null == setting)
                setting = new Config.EffectScript.BulletSetting();

            setting.target_type = (BulletTargetType)EditorGUILayout.EnumPopup("target type", setting.target_type);
            setting.move_speed = EditorGUILayout.FloatField("move_speed", setting.move_speed);
            setting.calibre = EditorGUILayout.FloatField("calibre", setting.calibre);
            setting.max_alive_sec = EditorGUILayout.FloatField("max_alive_sec", setting.max_alive_sec);
            setting.body_radius = EditorGUILayout.FloatField("body_radius", setting.body_radius);
            setting.model_id = EditorGUILayout.IntField("model_id", setting.model_id);
            setting.hit_filter_id = EditorGUILayout.IntPopup("hit_filter_id", setting.hit_filter_id,
                 editorData.filterTabData.GetCfgNames().ToArray(), editorData.filterTabData.GetCfgIds().ToArray());

            cfg.json_param = JsonConvert.SerializeObject(setting);
        }
    }
}
