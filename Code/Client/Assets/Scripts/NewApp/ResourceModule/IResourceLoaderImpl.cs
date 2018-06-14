

namespace Utopia
{
    public interface IResourceLoaderImpl
    {
        UnityEngine.Object Load(string path);
        void AsyncLoad(string path, System.Action<UnityEngine.Object> cb);
    }
}