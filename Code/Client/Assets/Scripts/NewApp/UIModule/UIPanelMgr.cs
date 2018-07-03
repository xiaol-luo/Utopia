
using System.Collections.Generic;

namespace Utopia.UI
{
    public class UIPanelMgr
    {
        public const string Default_UIPanelProxy_Res_Path = "Assets/Resources/UI/UIPanelProxy.prefab";

        static List<string> s_UIPanelProxy_Res_Paths = new List<string>() {
            Default_UIPanelProxy_Res_Path,
        };

        ResourceLoaderProxy m_resLoader = ResourceLoaderProxy.Create();

        Dictionary<string, ResourceObserver> m_panelProxyResMap = new Dictionary<string, ResourceObserver>();

        public ResourceObserver GetProxyGoRes(string resName)
        {
            ResourceObserver ret;
            m_panelProxyResMap.TryGetValue(resName, out ret);
            return ret;
        }

        public bool Init()
        {
            foreach (string resPath in s_UIPanelProxy_Res_Paths)
            {
               ResourceObserver resOb = m_resLoader.AsyncLoadAsset(resPath, null);
                m_panelProxyResMap.Add(resPath, resOb);
            }
            
            return true;
        }

        public void Destory()
        {
            m_resLoader.Release();
        }
    }
}
