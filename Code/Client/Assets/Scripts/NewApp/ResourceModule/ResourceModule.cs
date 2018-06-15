using UnityEngine;
using System.Collections;

namespace Utopia
{
    public class ResourceModule : AppModule
    {
        public ResourceModule(NewApp _app) : base(_app, EModule.ResourceModule)
        {

        }

        string resPath = "Assets/Resources/Heros/xiaoqiao_blue.prefab";
        bool isFirst = true;

        protected override void OnUpdate()
        {
            if (!isFirst)
                return;

            isFirst = false;

            ResourceObserver ret = null;
            ResourceObserver ret2 = ResourceLoader.instance.LoadAsset(resPath);
            GameObject.Instantiate(ret2.res);
            ret = ResourceLoader.instance.AsyncLoadAsset(resPath, (string xxx, UnityEngine.Object res) => {
                app.logModule.LogDebug(" ResouceModule AsyncLoad {0}", res.ToString());

                GameObject go = GameObject.Instantiate(ret.resState.req.res) as GameObject;
                GameObject go2 = GameObject.Instantiate(go);

                int id1 = go.GetInstanceID();
                int id2 = ret.resState.req.res.GetInstanceID();
                int id3 = go2.GetInstanceID();
                ret.Release();
            });
            app.root.StartCoroutine(CoLoadRes());
            ret2.Release();
            ret2.Release();
        }

        IEnumerator CoLoadRes()
        {
            ResourceObserver resOb = ResourceLoader.instance.CoLoadAsset(resPath);
            yield return resOb.resState.req;
            app.logModule.LogDebug(" ResouceModule CoLoadRes {0}", resOb.resState.req.res.ToString());

            if (null != resOb.res)
                GameObject.Instantiate(resOb.res);

            resOb.Release();
        }
    }
}

