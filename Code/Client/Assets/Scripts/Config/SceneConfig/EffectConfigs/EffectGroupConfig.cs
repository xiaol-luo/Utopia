
using System.Collections.Generic;

namespace Config
{
    public class EffectGroupConfig
    {
        public int id;
        public List<string> begin_effect_ids = new List<string>();
        public List<string> end_effect_ids = new List<string>();
        public List<TimeLineEffectStruct> timeline_effect_ids = new List<TimeLineEffectStruct>();
        public bool need_guide;
        public bool can_cancel_guide;
    }
}