
using System;
using UnityEngine;

namespace Utopia
{
    public class ResourceLoaderImplEditor : IResourceLoaderImpl
    {
        public void AsyncLoad(string path, Action<UnityEngine.Object> cb)
        {
            NewApp.instance.timerModule.Add(() =>
            {
                UnityEngine.Object res = this.Load(path);
                cb(res);
            }, 0);
        }

        public UnityEngine.Object Load(string path)
        {
            UnityEngine.Object ret = UnityEditor.AssetDatabase.LoadAssetAtPath<UnityEngine.Object>(path);
            return ret;
        }
    }
}