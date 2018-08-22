
using System.Collections.Generic;

namespace Config
{
    public class EffectSearcherConfig : EffectConfigBase
    {
        public int filter_id;
        public bool is_extract;
        public List<int> effect_ids = new List<int>();
    }
}