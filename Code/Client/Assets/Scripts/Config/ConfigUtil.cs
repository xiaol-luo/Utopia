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
                outVal = (0 != int.Parse(str));
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
            if (string.IsNullOrEmpty(strs))
                return true;

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
                    break;
                }
            }
            return all_ok;
        }

        public static bool Str2Map<K, V>(string strs, ref Dictionary<K, V> outDict)
        {
            if (string.IsNullOrEmpty(strs))
                return true;

            // k1:v1; k2:v2
            bool all_ok = true;
            foreach (string str in strs.Split(';'))
            {
                string[] kv_strs = str.Split(':');
                if (kv_strs.Length < 2 || string.IsNullOrEmpty(kv_strs[0]) || string.IsNullOrEmpty(kv_strs[1]))
                    all_ok = false;
                try
                {
                    K key = (K)Convert.ChangeType(kv_strs[0], typeof(K));
                    V val = (V)Convert.ChangeType(kv_strs[1], typeof(V));
                    outDict.Add(key, val);
                }
                catch (Exception)
                {
                    all_ok = false;
                    break;
                }
            }
            return all_ok;
        }

        public static bool Str2VecVec<T>(string strs, ref List<List<T>> outList)
        {
            if (string.IsNullOrEmpty(strs))
                return true;

            // a1|a2; b1|b2
            bool all_ok = true;
            foreach (string str in strs.Split(';'))
            {
                if (!all_ok)
                    break;

                List<T> val_vec = new List<T>();
                outList.Add(val_vec);

                if (!string.IsNullOrEmpty(str))
                {
                    foreach (string val_str in str.Split('|'))
                    {
                        try
                        {
                            T tmp_val = (T)Convert.ChangeType(str, typeof(T));
                            val_vec.Add(tmp_val);
                        }
                        catch (Exception)
                        {
                            all_ok = false;
                            break;
                        }
                    }
                }
            }
            return all_ok;
        }

        public static bool Str2MapVec<K, V>(string strs, ref Dictionary<K, List<V>> outDict)
        {
            if (string.IsNullOrEmpty(strs))
                return true;

            // k1:v1|v2; kk1: vv1|vv2
            bool all_ok = true;
            foreach (string str in strs.Split(';'))
            {
                string[] kv_strs = str.Split(':');
                if (kv_strs.Length < 2 || string.IsNullOrEmpty(kv_strs[0]))
                {
                    all_ok = false;
                    break;
                }
                try
                {
                    K key = (K)Convert.ChangeType(kv_strs[0], typeof(K));
                    List<V> val_vec = new List<V>();
                    outDict.Add(key, val_vec);
                    if (!string.IsNullOrEmpty(kv_strs[1]))
                    {
                        foreach (string val_str in kv_strs[1].Split('|'))
                        {
                            V val = (V)Convert.ChangeType(kv_strs[1], typeof(V));
                            val_vec.Add(val);
                        }
                    }
                }
                catch (Exception)
                {
                    all_ok = false;
                    break;
                }
            }
            return all_ok;
        }
    }
}
