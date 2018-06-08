
namespace Utopia
{
    public class AppModule
    {
        public enum EStage
        {
            Free,
            Inited,
            Awaking,
            Awaked,
            Staring,
            Started,
            Updating,
            Quiting,
            Quited,
        }
        protected int m_moduleId = NewApp.EModule.Count;
        public int moduleId { get { return m_moduleId; } }
        public EStage stage { get; set; }
        public enum ERet
        {
            Success,
            Fail,
            Pending,
        }
        public struct EModule
        {
            public const int UIMgr = 0;
            public const int CameraMgr = 1;
            public const int Count = 3;
        }

        public AppModule(NewApp _app, int moduleId)
        {
            _app = app;
            m_moduleId = moduleId;
        }
        public NewApp app { get; }

        delegate ERet FnToCall();
        ERet CallUtil(EStage fromStage, EStage toStage, FnToCall fn)
        {
            if (toStage == stage)
                return ERet.Success;
            if (fromStage != stage)
                return ERet.Fail;
            ERet ret = fn();
            if (ERet.Success == ret)
                stage = toStage;
            return ret;
        }

        public void Init()
        {
            if (EStage.Free == stage)
            {
                this.OnInit();
                stage = EStage.Inited;
            }
        }
        public ERet Awake()
        {
            ERet ret = CallUtil(EStage.Awaking, EStage.Awaked, this.OnAwake);
            return ret;
        }
        public ERet Start()
        {
            ERet ret = CallUtil(EStage.Staring, EStage.Started, this.OnStart);
            return ret;
        }
        public void Update()
        {
            if (EStage.Updating != stage)
                return;
            this.OnUpdate();
        }
        public void LateUpdate()
        {
            if (EStage.Updating != stage)
                return;
            this.OnLateUpdate();
        }
        public void FixedUpdate()
        {
            if (EStage.Updating == stage)
                return;
            this.OnFixedUpdate();
        }
        public ERet Quit()
        {
            ERet ret = CallUtil(EStage.Quiting, EStage.Quited, this.OnQuit);
            return ret;
        }

        protected virtual void OnInit() { }
        protected virtual ERet OnAwake() { return ERet.Success; }
        protected virtual ERet OnStart() { return ERet.Success; }

        protected virtual void OnUpdate() { }

        protected virtual void OnLateUpdate() { }

        protected virtual void OnFixedUpdate() { }
        protected virtual ERet OnQuit() { return ERet.Success; }
    }
}
