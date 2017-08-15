#include "CsvConfigSets.h"
#include "log/CsvLogConfig.h"

namespace Config
{
    CsvConfigSets::~CsvConfigSets()
    {
        delete csv_CsvLogConfigSet;
    }

    bool CsvConfigSets::Load(std::string root_path)
    {
        while (!root_path.empty())
        {
            if (root_path.back() != '\\' && root_path.back() != '/' && root_path.back() != ' ')
                break;
            root_path.pop_back();
        }
        csv_CsvLogConfigSet = new CsvLogConfigSet;

        bool all_ok = true;
        if (all_ok)
        {
            all_ok = csv_CsvLogConfigSet->Load(root_path + '/' + "Log/CsvLogConfig.csv");
        }

        if (!all_ok)
        {
            delete csv_CsvLogConfigSet; csv_CsvLogConfigSet = nullptr;
        }

        return all_ok;
    }
}