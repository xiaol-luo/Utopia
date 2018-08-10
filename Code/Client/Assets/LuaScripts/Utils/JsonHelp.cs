using UnityEngine;
using UnityEditor;
using System.IO;
using System;
using Newtonsoft.Json;

public static class JsonHelp 
{
    public static T LoadStruct<T>(string filePath) where T : new()
    {
        try
        {
            if (File.Exists(filePath))
            {
                string txt = File.ReadAllText(filePath);
                T ret = JsonConvert.DeserializeObject<T>(txt);
                return ret;
            }
        }
        catch(Exception e)
        {
            Debug.LogErrorFormat("JsonHelp.LoadStruct {0}, {1}", filePath, e.Message);
        }
        return new T();
    }

    public static bool SaveStruct<T>(string filePath, T val)
    {
        try
        {
            if (!File.Exists(filePath))
            {
                string dirName = Path.GetDirectoryName(filePath);
                if (!Directory.Exists(dirName))
                {
                    Directory.CreateDirectory(dirName);
                }
            }
            var fd = File.Create(filePath);
            fd.Close();
            string txt = JsonConvert.SerializeObject(val, Formatting.Indented);
            File.WriteAllText(filePath, txt);
            return true;
        }
        catch (Exception e)
        {
            Debug.LogErrorFormat("JsonHelp.LoadStruct {0}, {1}", filePath, e.Message);
        }
        return false;
    }
}
