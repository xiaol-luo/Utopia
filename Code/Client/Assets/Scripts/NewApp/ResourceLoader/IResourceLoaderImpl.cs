

namespace Utopia
{
    public interface IResourceLoaderImpl
    {
        UnityEngine.Object Load(string path);
        void AsyncLoad(string path, System.Action<string, UnityEngine.Object> cb);
        void Unload(string path);

        bool LoadScene(string path);
        void AsyncLoadScene(string path, System.Action<string, bool> cb);
        void UnloadScene(string path);
    }
}