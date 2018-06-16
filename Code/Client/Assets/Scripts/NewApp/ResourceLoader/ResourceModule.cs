using UnityEngine;
using System.Collections;
using System;

namespace Utopia
{
    public class ResourceModule : AppModule
    {
        public ResourceModule(NewApp _app) : base(_app, EModule.ResourceModule)
        {

        }

        string resPath = "Assets/Resources/Heros/xiaoqiao_blue.prefab";
        bool isFirst = true;
        ResourceLoaderProxy loader = ResourceLoaderProxy.Create();

        long m_firstTick = 0;

        protected override void OnUpdate()
        {
            if (!isFirst)
            {
                if (m_firstTick > 0 && app.datetimeModule.now.Ticks - m_firstTick > TimeSpan.TicksPerSecond * 20)
                {
                    m_firstTick = 0;
                    loader.Release();
                }
                return;
            }

            isFirst = false;
            m_firstTick = app.datetimeModule.now.Ticks;

            ResourceObserver ret2 = loader.LoadAsset(resPath);
            var tmpGo = ret2.Instantiate<GameObject>();

            ResourceObserver ret = null;
            ret = loader.AsyncLoadAsset(resPath, (string xxx, ResourceObserver res) => {
                app.logModule.LogDebug(" ResouceModule AsyncLoad {0}", res.ToString());

                GameObject go = ret.Instantiate<GameObject>();
                int id1 = go.GetInstanceID();
                int id2 = ret.resState.req.res.GetInstanceID();

                GameObject.Destroy(go);
            });
            app.root.StartCoroutine(CoLoadRes());
            GameObject.Destroy(tmpGo);
        }

        IEnumerator CoLoadRes()
        {
            ResourceObserver resOb = loader.CoLoadAsset(resPath);
            yield return resOb.resState.req;
            if (resOb.isValid)
            {
                app.logModule.LogDebug(" ResouceModule CoLoadRes {0}", resOb.resState.req.res.ToString());
                GameObject.Destroy(resOb.Instantiate<GameObject>());
            }
        }
    }
}

