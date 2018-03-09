#include "ConfigUtil.h"

namespace ConfigUtil
{
	void Trim(std::string &val, std::set<char> chars)
	{
		if (chars.empty())
			return;

		{
			int len = 0;
			for (auto it = val.begin(); val.end() != it; ++it)
			{
				if (chars.count(*it) <= 0)
					break;
			}
			if (len > 0)
				val.erase(0, len);
		}
		{
			int len = 0;
			for (auto it = val.rbegin(); val.rend() != it; ++it)
			{
				if (chars.count(*it) <= 0)
					break;
			}
			if (len > 0)
				val.erase(0, len);
		}
	}

	static std::set<char> DEFAULT_TRIM_CHARS({' ', '\t'});
	void Trim(std::string &val)
	{
		Trim(val, DEFAULT_TRIM_CHARS);
	}

	bool Str2BaseValue(std::string s, bool &out_val)
    {
        try 
        {
			Trim(s);
			int int_val = s.empty() ? 0 : std::stoi(s);
            out_val = (0 != int_val);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2BaseValue(std::string s, int &out_val)
    {
        try 
        {
			Trim(s);
            out_val = s.empty() ? 0 : std::stoi(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2BaseValue(std::string s, float &out_val)
    {
        try 
        {
			Trim(s);
            out_val = s.empty() ? 0 : std::stof(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }
    
    bool Str2BaseValue(std::string s, double &out_val)
    {
        try 
        {
			Trim(s);
            out_val = s.empty() ? 0 : std::stod(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

    bool Str2BaseValue(std::string s, long long &out_val)
    {
        try 
        {
			Trim(s);
            out_val = s.empty() ? 0 : std::stoll(s);
            return true;
        }
        catch (std::exception e)
        {
            return false;
        }
    }

	bool Str2BaseValue(std::string s, std::string & out_val)
	{
		Trim(s);
		out_val = s;
		return true;
	}

    bool Str2Str(std::string s, std::string &out_val)
    {
		Trim(s);
        out_val = s;
        return true;
    }

    std::vector<std::string> SplitStr(const std::string &s, char c)
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