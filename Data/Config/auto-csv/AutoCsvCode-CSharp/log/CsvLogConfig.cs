using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Config
{
    public class CsvLogConfig
    {
        public int id = 0;
        public List<int> alsoWriteToMe = new List<int>();
        public int logger_type = 0;
        public string save_file;
        public int rorating_max_size = 0;
        public int rorating_max_files = 0;
        public int daily_hour = 0;
        public int daily_min = 0;

        public delegate bool ConfigCheckFunc(CsvLogConfig cfg);
        public bool Init(Dictionary<string, string> kvPairs, ConfigCheckFunc func)
        {
            return true;
        }
    }

    public class CsvLogConfigSet
    {
        CsvLogConfig.ConfigCheckFunc cfg_check_fun = null;
        public delegate bool ConfigSetCheckFunc(CsvLogConfigSet items);
        ConfigSetCheckFunc cfg_set_check_fun = null;

        bool Load(string file_path)
        {
            return true;
        }

        List<CsvLogConfig> cfg_vec;
        Dictionary<int, CsvLogConfig> id_to_key;
    }
}
