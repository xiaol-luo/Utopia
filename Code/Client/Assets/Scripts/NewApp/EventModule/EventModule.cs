namespace Utopia
{
    public class EventModule : AppModule
    {
        public EventMgr<string> m_eventMgr = new EventMgr<string>();

        public EventModule(NewApp _app) : base(_app, EModule.EventModule)
        {

        }
    }
}

