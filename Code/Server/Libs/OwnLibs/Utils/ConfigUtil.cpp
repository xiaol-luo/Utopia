#include "ConfigUtil.h"

namespace ConfigUtil
{
     bool Str2BaseValue(const std::string & s, bool &out_val)
    {
        try 
        {
            int int_val = std::stoi(s);
            out_val = (0 != int_val);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2BaseValue(const std::string & s, int &out_val)
    {
        try 
        {
            out_val = std::stoi(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2BaseValue(const std::string & s, float &out_val)
    {
        try 
        {
            out_val = std::stof(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }
    
    bool Str2BaseValue(const std::string & s, double &out_val)
    {
        try 
        {
            out_val = std::stod(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2BaseValue(const std::string & s, long long &out_val)
    {
        try 
        {
            out_val = std::stoll(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2Str(const std::string & s, std::string &out_val)
    {
        out_val = s;
        return true;
    }

    std::vector<std::string> SplitStr(const std::string s, char c)
    {
        std::vector<std::string> str_vec;
        auto last_it = s.begin();
        auto curr_it = s.begin();
        for (curr_it; curr_it != s.end(); ++ curr_it)
        {
            if (*curr_it == c)
            {
                if (last_it != curr_it)
                    str_vec.push_back(std::string(last_it, curr_it));
                last_it = curr_it + 1;
            }
        }
        if (curr_it != last_it)
            str_vec.push_back(std::string(last_it, curr_it));
        return str_vec;
    }
}