

namespace Utopia
{
    public interface IResourceLoaderImpl
    {
        UnityEngine.Object Load(string path);
        void AsyncLoad(string path, System.Action<string, UnityEngine.Object> cb);

        void Unload(string path);
    }
}