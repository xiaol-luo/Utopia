
using System;
using UnityEngine;

namespace Utopia
{
    public class ResourceLoaderImplAB : IResourceLoaderImpl
    {
        public void AsyncLoad(string path, Action<UnityEngine.Object> cb)
        {
            throw new NotImplementedException();
        }

        public UnityEngine.Object Load(string path)
        {
            throw new NotImplementedException();
        }
    }
}

