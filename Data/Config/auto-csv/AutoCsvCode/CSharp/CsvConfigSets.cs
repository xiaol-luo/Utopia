using System;
using System.IO;

namespace Config
{
    public class CsvConfigSets
    {
        public string errMsg = string.Empty;
        public CsvLogConfigSet csv_CsvLogConfigSet = new CsvLogConfigSet();
        public CsvSceneConfigSet csv_CsvSceneConfigSet = new CsvSceneConfigSet();

        public bool Load(string root_path)
        {
            if (!csv_CsvLogConfigSet.Load(Path.Combine(root_path, "Log/CsvLogConfig.csv")))
            {
                errMsg = "Load csv_CsvLogConfigSet fail";
                return false;
            }
            if (!csv_CsvSceneConfigSet.Load(Path.Combine(root_path, "scene/CsvSceneConfig.csv")))
            {
                errMsg = "Load csv_CsvSceneConfigSet fail";
                return false;
            }

            return true;
        }
    }
}