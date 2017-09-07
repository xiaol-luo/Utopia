using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Config
{
    class ConfigUtil
    {
        public static bool Str2BaseValue(string str, ref bool outVal)
        {
            try
            {
                outVal = bool.Parse(str);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        public static bool Str2BaseValue(string str, ref int outVal)
        {
            try
            {
                outVal = int.Parse(str);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        public static bool Str2BaseValue(string str, ref float outVal)
        {
            try
            {
                outVal = float.Parse(str);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        public static bool Str2BaseValue(string str, ref double outVal)
        {
            try
            {
                outVal = double.Parse(str);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        public static bool Str2BaseValue(string str, ref long outVal)
        {
            try
            {
                outVal = long.Parse(str);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        public static bool Str2Str(string str, ref string outStr)
        {
            outStr = str;
            return true;
        }

        public static bool Str2Vec<T>(string strs, ref List<T> outVec)
        {
            // v1; v2
            bool all_ok = true;
            foreach (string str in strs.Split(';'))
            {
                try
                {
                    T tmp_val = (T)Convert.ChangeType(str, typeof(T));
                    outVec.Add(tmp_val);
                }
                catch (Exception)
                {
                    all_ok = false;
                }
            }
            return all_ok;
        }

        public static bool Str2Map<K, V>(string str, ref Dictionary<K, V> outDict)
        {
            return true;
        }

        public static bool Str2VecVec<T>(string str, ref List<List<T>> outList)
        {
            return true;
        }

        public static bool Str2MapVec<K, V>(string str, ref Dictionary<K, List<V>> outDict)
        {
            return true;
        }
    }
}
