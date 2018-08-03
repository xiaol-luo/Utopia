using System;
using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Utopia
{
    public class ResourceScene : CustomYieldInstruction
    {
        ResourceLoader m_resLoader;
        public ResourceLoader resLoader { get { return m_resLoader; } }

        ResourceState m_resState;
        public ResourceState resState { get { return m_resState; } }
        UnityEngine.AsyncOperation m_resOpera;
        UnityEngine.Coroutine m_resOperaCo;
        public bool isAddition;

        protected LoadSceneMode loadSceneMode 
        {
            get
            {
                return isAddition ? LoadSceneMode.Additive : LoadSceneMode.Single;
            }
        }

        public enum LoadResult
        {
            Succ,
            Fail,
            Cancel,
        };

        public enum State
        {
            Invalid,
            Inited,
            LoadingAsset,
            LoadingScene,
            Loaded,
            Fail,
            Released,
        }
        State m_state = State.Invalid;
        public State state { get { return m_state; } }

        public bool isDone
        {
            get
            {
                bool ret = true;
                switch (m_state)
                {
                    case State.Inited:
                    case State.LoadingAsset:
                    case State.LoadingScene:
                        ret = false;
                        break;
                }
                return ret;
            }
        }
        public bool isLoading
        {
            get
            {
                bool ret = false;
                switch (m_state)
                {
                    case State.LoadingAsset:
                    case State.LoadingScene:
                        ret = true;
                        break;
                }
                return ret;
            }
        }
        public bool isLoaded
        {
            get
            {
                bool ret = State.Loaded == m_state;
                return ret;
            }
        }

        public bool isLoadFail
        {
            get
            {
                bool ret = State.Fail == m_state;
                return ret;
            }
        }

        public bool isReleased
        {
            get
            {
                bool ret = State.Released == m_state;
                return ret;
            }
        }
        System.Action<ResourceScene.LoadResult, string> m_cb;
        public System.Action<ResourceScene.LoadResult, string> cb { get { return m_cb; } }
        public void SetCb(System.Action<ResourceScene.LoadResult, string> _cb) { m_cb = _cb; }

        public string sceneName
        {
            get
            {
                return resState.path;
            }
        }

        public override bool keepWaiting
        {
            get
            {
                return !isDone;
            }
        }

        public ResourceScene(ResourceState resState)
        {
            m_state = State.Inited;
            m_resState = resState;
            m_resLoader = resState.loader;
        }

        public void SetLoadAssetFail()
        {
            if (State.LoadingAsset == m_state)
            {
                m_state = State.Fail;
                resState.req.UnloadRes();
                if (null != m_cb)
                {
                    m_cb(LoadResult.Fail, this.sceneName);
                    this.SetCb(null);
                }
            }
        }
        public void Release()
        {
            m_state = State.Released;

            if (null != m_cb)
            {
                m_cb(LoadResult.Cancel, this.sceneName);
                this.SetCb(null);
            }
            m_resState.req.UnloadRes();
            if (null != m_resOperaCo)
            {
                Core.instance.StopCoroutine(m_resOperaCo);
                m_resOperaCo = null;
            }
            if (null != m_resOpera)
            {
                m_resOpera = null;
                SceneManager.UnloadSceneAsync(this.sceneName);
            }
        }
        public bool ReloadScene(System.Action<ResourceScene.LoadResult, string> newCb)
        {
            bool ret = false;
            if (this.isLoaded)
            {
                ret = true;
                m_state = State.LoadingScene;
                this.SetCb(newCb);
                SceneManager.UnloadSceneAsync(this.sceneName);
                m_resOpera = UnityEngine.SceneManagement.SceneManager.LoadSceneAsync(this.sceneName, this.loadSceneMode);
                m_resOperaCo = Core.instance.StartCoroutine(CoTryLoadScene());
            }
            return ret;
        }
        public bool TryLoadScene()
        {
            bool ret = false;
            if (State.LoadingAsset == m_state)
            {
                ret = true;
                m_state = State.LoadingScene;
                m_resOpera = UnityEngine.SceneManagement.SceneManager.LoadSceneAsync(this.sceneName, this.loadSceneMode);
                m_resOperaCo = Core.instance.StartCoroutine(CoTryLoadScene());
            }
            return ret;
        }
        IEnumerator CoTryLoadScene()
        {
            while (true)
            {
                if (null == m_resOpera || m_resOpera.isDone)
                    break;
                yield return new WaitForSeconds(0.001f);
            }
            if (null != m_resOpera && m_resOpera.isDone)
            {
                m_state = State.Loaded;
                if (null != m_cb)
                {
                    m_cb(LoadResult.Succ, this.sceneName);
                    this.SetCb(null);
                }
            }
            m_resOpera = null;
            m_resOperaCo = null;
        }

        public bool TryLoadAsset()
        {
            bool ret = false;
            if (State.Inited == m_state)
            {
                ret = true;
                m_state = State.LoadingAsset;
                resState.req.AsyncLoad();
            }
            return ret;
        }
    }
}