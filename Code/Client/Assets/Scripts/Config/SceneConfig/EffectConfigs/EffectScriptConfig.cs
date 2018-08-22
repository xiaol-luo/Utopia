
using System.Collections.Generic;

namespace Config
{
    public enum EEffectScriptType
    {
        Bullet,
    }

    public class EffectScriptSetting
    {
        public static Dictionary<EEffectScriptType, string> s_typeLuaClassMap = new Dictionary<EEffectScriptType, string>
        {
            {EEffectScriptType.Bullet, "effect_script.effect_bullet" }
        };
    }

    public class EffectScriptConfig : EffectConfigBase
    {
        public EEffectScriptType script_type;
        public string class_name = string.Empty;
        public string string_param = string.Empty;
        public string json_param = string.Empty;
        public int int_param;
    }
}

namespace Config.EffectScript
{
    public enum BulletTargetType
    {
        Pos,
        SceneUnit,
    }
    public class BulletSetting
    {
        public BulletTargetType target_type;
        public float max_alive_sec = 20.0f;
        public float move_speed;
        public float calibre;
        public int hit_filter_id;
        public int model_id;
        public float body_radius;
    }
}