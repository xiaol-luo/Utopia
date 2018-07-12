
namespace Utopia
{
    public class CoreModule
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
            Releasing,
            Released,
        }
        protected int m_moduleId = EModule.Count;
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
            public const int DateTimeModule = 0;
            public const int LogModule = 1;
            public const int TimerModule = 2;
            public const int EventModule = 3;
            public const int UIModule = 4;
            public const int CameraModule = 5;
            public const int NetModule = 6;
            public const int ResourceModule = 7;
            public const int Count = 8;
        }

        public CoreModule(Core _app, int moduleId)
        {
            app = _app;
            m_moduleId = moduleId;
        }
        public Core app { get; }

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
            if (EStage.Updating != stage)
                return;
            this.OnFixedUpdate();
        }
        public ERet Release()
        {
            ERet ret = CallUtil(EStage.Releasing, EStage.Released, this.OnRelease);
            return ret;
        }

        protected virtual void OnInit() { }
        protected virtual ERet OnAwake() { return ERet.Success; }
        protected virtual ERet OnStart() { return ERet.Success; }

        protected virtual void OnUpdate() { }

        protected virtual void OnLateUpdate() { }

        protected virtual void OnFixedUpdate() { }
        protected virtual ERet OnRelease() { return ERet.Success; }
    }
}
