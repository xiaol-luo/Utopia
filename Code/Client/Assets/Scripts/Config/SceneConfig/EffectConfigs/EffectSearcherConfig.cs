
using System.Collections.Generic;

namespace Config
{
    public class EffectSearcherConfig : EffectConfigBase
    {
        public int filter_id;
        public List<int> effect_ids = new List<int>();
    }
}