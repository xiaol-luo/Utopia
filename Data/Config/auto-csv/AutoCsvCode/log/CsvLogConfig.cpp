#include "log/CsvLogConfig.h"
#include "CsvParser/csv.h"

namespace Config
{
     static const char * Field_Name_prof = "prof";
     static const char * Field_Name_name = "name";
     static const char * Field_Name_hp = "hp";
     static const char * Field_Name_gongji = "gongji";
     static const char * Field_Name_moveSpeed = "moveSpeed";

    bool CsvLogConfig::Init(std::map<std::string, std::string> kvPairs, ConfigCheckFunc func)
    {
        bool all_ok = true;
        all_ok = all_ok && kvPairs.count(Field_Name_prof) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_prof], prof);
        all_ok = all_ok && kvPairs.count(Field_Name_name) > 0 && ConfigUtil::Str2Str (kvPairs[Field_Name_name], name);
        all_ok = all_ok && kvPairs.count(Field_Name_hp) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_hp], hp);
        all_ok = all_ok && kvPairs.count(Field_Name_gongji) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_gongji], gongji);
        all_ok = all_ok && kvPairs.count(Field_Name_moveSpeed) > 0 && ConfigUtil::Str2BaseValue (kvPairs[Field_Name_moveSpeed], moveSpeed);
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
        io::CSVReader<5, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>, io::no_comment> csv_reader(file_path);
        csv_reader.read_header(io::ignore_extra_column,
            Field_Name_prof,
            Field_Name_name,
            Field_Name_hp,
            Field_Name_gongji,
            Field_Name_moveSpeed
            );

        std::map<std::string, std::string> kvParis;
        kvParis[Field_Name_prof] = "";
        kvParis[Field_Name_name] = "";
        kvParis[Field_Name_hp] = "";
        kvParis[Field_Name_gongji] = "";
        kvParis[Field_Name_moveSpeed] = "";

        bool all_ok = true;
        int curr_row = 0;
        while (csv_reader.read_row(
            kvParis[Field_Name_prof],
            kvParis[Field_Name_name],
            kvParis[Field_Name_hp],
            kvParis[Field_Name_gongji],
            kvParis[Field_Name_moveSpeed]
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
            }
        }
        if (nullptr != cfg_set_check_fun)
        {
            all_ok = all_ok && cfg_set_check_fun((void *)this);
        }
        return all_ok;
    }
}
