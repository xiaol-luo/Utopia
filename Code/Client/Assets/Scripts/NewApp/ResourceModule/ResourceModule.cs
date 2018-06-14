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

            UnityEngine.Object ret = null;
            ret = ResourceLoader.instance.LoadAsset(resPath);
            ResourceObserver xx = null;
            xx = ResourceLoader.instance.AsyncLoadAsset(resPath, (bool xxx, UnityEngine.Object res) => {
                app.logModule.LogDebug(" ResouceModule AsyncLoad {0}", res.ToString());

                xx.Release();
            });
            app.root.StartCoroutine(CoLoadRes());
        }

        IEnumerator CoLoadRes()
        {
            ResourceObserver resOb = ResourceLoader.instance.CoLoadAsset(resPath);
            yield return resOb.resState.req;
            app.logModule.LogDebug(" ResouceModule CoLoadRes {0}", resOb.resState.req.res.ToString());
            resOb.Release();
        }
    }
}

