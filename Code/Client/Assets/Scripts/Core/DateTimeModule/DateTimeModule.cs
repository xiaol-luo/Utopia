using System;

namespace Utopia
{
    public class DateTimeModule : CoreModule
    {
        public DateTimeModule(Core _app) : base(_app, EModule.DateTimeModule)
        {

        }


        public DateTime now {
            get
            {
                return DateTime.Now;
            }
        }
        public DateTime srvNow
        {
            get
            {
                DateTime ret = DateTime.Now.AddSeconds(m_srvDeltaSecs);
                return ret;
            }
        }

        protected long m_srvDeltaSecs = 0;
        long SyncTimeSpan = TimeSpan.TicksPerSecond * 10;
        long m_nextSyncTimeTick = 0;

        public void TrySyncSrvTime()
        {

        }
        void OnSyncSrvTime()
        {

        }

        protected override void OnFixedUpdate()
        {
            long nowTick = this.now.Ticks;
            if (nowTick >= m_nextSyncTimeTick)
            {
                m_nextSyncTimeTick = nowTick + SyncTimeSpan;
                this.TrySyncSrvTime();
            }
        }
    }
}

