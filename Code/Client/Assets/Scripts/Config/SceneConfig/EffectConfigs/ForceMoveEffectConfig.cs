
namespace Config
{
    public enum MoveSetting
    {
        TimeSpeed,
        TimeDistance,
        DistanceSpeed
    }

    public class ForceMoveEffectConfig : EffectConfigBase
    {
        public bool ignore_terrian;
        public MoveSetting move_setting;
        public float move_sec = 1.0f;
        public float move_speed = 1.0f;
        public float move_distance = 1.0f;
        public EEffectFilterAnchor anchor;
        public float angle;
    }
}