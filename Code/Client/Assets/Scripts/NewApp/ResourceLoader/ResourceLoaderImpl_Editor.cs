
using System;
using UnityEngine;

namespace Utopia
{
    public class ResourceLoaderImplEditor : IResourceLoaderImpl
    {
        public void AsyncLoad(string path, Action<string, UnityEngine.Object> cb)
        {
            NewApp.instance.timerModule.Add(() =>
            {
                UnityEngine.Object res = this.Load(path);
                cb(path, res);
            }, 0);
        }

        public void AsyncLoadScene(string path, Action<string, bool> cb)
        {
            NewApp.instance.timerModule.Add(() =>
            {
                bool ret = this.Load(path);
                cb(path, ret);
            }, 0);
        }

        public UnityEngine.Object Load(string path)
        {
            UnityEngine.Object ret = UnityEditor.AssetDatabase.LoadAssetAtPath<UnityEngine.Object>(path);
            return ret;
        }

        public bool LoadScene(string path)
        {
            return true;
        }

        public void Unload(string path)
        {

        }

        public void UnloadScene(string path)
        {
            
        }
    }
}