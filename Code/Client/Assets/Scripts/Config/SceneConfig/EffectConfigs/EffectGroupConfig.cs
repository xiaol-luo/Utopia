
using System.Collections.Generic;

namespace Config
{
    public class EffectGroupConfig
    {
        public int id;
        public string name = string.Empty;
        public List<int> begin_effect_ids = new List<int>();
        public List<EncCaseEffectStruct> end_effect_ids = new List<EncCaseEffectStruct>();
        public List<TimeLineEffectStruct> timeline_effect_ids = new List<TimeLineEffectStruct>();
        public bool need_guide;
        public bool can_cancel_guide;
    }
}