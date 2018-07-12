using UnityEngine;
using System.Collections;
using System;

namespace Utopia
{
    public class ResourceModule : CoreModule
    {
        public ResourceModule(Core _app) : base(_app, EModule.ResourceModule)
        {

        }

        string resPath = "Assets/Resources/Heros/xiaoqiao_blue.prefab";
        bool isFirst = true;
        ResourceLoaderProxy loader = ResourceLoaderProxy.Create();

        long m_firstTick = 0;

        protected override void OnUpdate()
        {
            return;

            if (!isFirst)
            {
                if (m_firstTick > 0 && app.datetime.now.Ticks - m_firstTick > TimeSpan.TicksPerSecond * 20)
                {
                    m_firstTick = 0;
                    loader.Release();
                }
                return;
            }

            isFirst = false;
            m_firstTick = app.datetime.now.Ticks;

            string scenePath = "Assets/Resources/Levels/Level_Battle.unity";
            /*
            for (int i = 0; i < 1; ++ i)
            {
                int xxx = i;
                ResourceLoader.instance.AsyncLoadScene(scenePath, true, (ResourceScene.LoadResult lr, string sceneName) =>
                {
                    app.log.LogDebug(" ResouceModule AsyncLoadScene {0} {1} {2}", sceneName, lr, xxx);
                });
            }
            */

            //             ResourceLoader.instance.UnloadScene(scenePath);

            {
                Core.instance.StartCoroutine(CoLoadScene(scenePath));
            }


            ResourceObserver ret2 = loader.LoadAsset(resPath);
            var tmpGo = ret2.Instantiate<GameObject>();

            ResourceObserver ret = null;
            ret = loader.AsyncLoadAsset(resPath, (string xxx, ResourceObserver res) => {
                app.log.LogDebug(" ResouceModule AsyncLoad {0}", res.ToString());

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
                app.log.LogDebug(" ResouceModule CoLoadRes {0}", resOb.resState.req.res.ToString());
                GameObject.Destroy(resOb.Instantiate<GameObject>());
            }
        }

        IEnumerator CoLoadScene(string scenePath)
        {
            ResourceScene ie = ResourceLoader.instance.CoLoadScene(scenePath, false);
            yield return ie;
            app.log.LogDebug(" ResouceModule CoLoadScene");
            yield return null;
        }
    }
}

