

namespace Config
{
    public enum EffectEndCase
    {
        Both = 0,
        Done,
        Break,
    }
    public class EncCaseEffectStruct
    {
        public EffectEndCase end_case;
        public int effect_id;
    }
}