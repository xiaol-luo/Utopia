
using System.Collections.Generic;

namespace Config
{
    public class AttrScriptConfig
    {
        public int id;
        public List<AttrKvStruct> base_attrs = new List<AttrKvStruct>();
        public List<AttrKvStruct> extra_attrs = new List<AttrKvStruct>();
        public List<AttrKvStruct> percent_attrs = new List<AttrKvStruct>();
        public int hold_ms;
        public int unique_id;

    }
}