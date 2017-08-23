#include "log/CsvLogConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_id = "id";
     static const char * Field_Name_alsoWritetoMe = "alsoWritetoMe";
     static const char * Field_Name_logger_type = "logger_type";
     static const char * Field_Name_name = "name";
     static const char * Field_Name_log_level = "log_level";
     static const char * Field_Name_save_file = "save_file";
     static const char * Field_Name_rorating_max_size = "rorating_max_size";
     static const char * Field_Name_rorating_max_files = "rorating_max_files";
     static const char * Field_Name_daily_hour = "daily_hour";
     static const char * Field_Name_daily_min = "daily_min";

    bool CsvLogConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_id) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_id], id);
        all_ok = all_ok && kvPairs.count(Field_Name_alsoWritetoMe) > 0 && ConfigUtil::Str2Vec (kvPairs[Field_Name_alsoWritetoMe], alsoWritetoMe);
        all_ok = all_ok && kvPairs.count(Field_Name_logger_type) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_logger_type], logger_type);
        all_ok = all_ok && kvPairs.count(Field_Name_name) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_name], name);
        all_ok = all_ok && kvPairs.count(Field_Name_log_level) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_log_level], log_level);
        all_ok = all_ok && kvPairs.count(Field_Name_save_file) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_save_file], save_file);
        all_ok = all_ok && kvPairs.count(Field_Name_rorating_max_size) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_rorating_max_size], rorating_max_size);
        all_ok = all_ok && kvPairs.count(Field_Name_rorating_max_files) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_rorating_max_files], rorating_max_files);
        all_ok = all_ok && kvPairs.count(Field_Name_daily_hour) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_daily_hour], daily_hour);
        all_ok = all_ok && kvPairs.count(Field_Name_daily_min) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_daily_min], daily_min);
        if (all_ok && nullptr != func)
            all_ok &= func(this);
        return all_ok;
    }

    CsvLogConfigSet::~CsvLogConfigSet()
    {
        for (auto cfg : cfg_vec)
        {
            delete cfg;
        }
    }

    bool CsvLogConfigSet::Load(std::string file_path)
    {
        io::CSVReader<10, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_id,
            Field_Name_alsoWritetoMe,
            Field_Name_logger_type,
            Field_Name_name,
            Field_Name_log_level,
            Field_Name_save_file,
            Field_Name_rorating_max_size,
            Field_Name_rorating_max_files,
            Field_Name_daily_hour,
            Field_Name_daily_min
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_id] = "";
        kvParis[Field_Name_alsoWritetoMe] = "";
        kvParis[Field_Name_logger_type] = "";
        kvParis[Field_Name_name] = "";
        kvParis[Field_Name_log_level] = "";
        kvParis[Field_Name_save_file] = "";
        kvParis[Field_Name_rorating_max_size] = "";
        kvParis[Field_Name_rorating_max_files] = "";
        kvParis[Field_Name_daily_hour] = "";
        kvParis[Field_Name_daily_min] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_id],
            kvParis[Field_Name_alsoWritetoMe],
            kvParis[Field_Name_logger_type],
            kvParis[Field_Name_name],
            kvParis[Field_Name_log_level],
            kvParis[Field_Name_save_file],
            kvParis[Field_Name_rorating_max_size],
            kvParis[Field_Name_rorating_max_files],
            kvParis[Field_Name_daily_hour],
            kvParis[Field_Name_daily_min]
            ))
        {            
            if (++ curr_row <= 1)
                continue;
            CsvLogConfig *cfg = new CsvLogConfig();
            all_ok &= cfg->Init(kvParis, cfg_check_fun);
            if (!all_ok)
                break;
            cfg_vec.push_back(cfg);
        }
        if (all_ok)
        {
            // gen key
            for (auto cfg : cfg_vec)
            {
                {
                    if (id_to_key.count(cfg->id) > 0)
                    {
                        all_ok = false;
                        break;
                    }
                    id_to_key[cfg->id] = cfg;
                }
            }
        }
        if (nullptr != cfg_set_check_fun)
        {
            all_ok = all_ok && cfg_set_check_fun((void *)this);
        }
        return all_ok;
    }
}
