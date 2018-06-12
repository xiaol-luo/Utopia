using System;
using System.Collections.Generic;

namespace Utopia
{
    using TimerId = System.UInt64;

    public class TimerModule : AppModule
    {
        public TimerModule(NewApp _app) : base(_app, EModule.TimerModule)
        {
            
        }

        class Item : IComparable<Item>
        {
            public TimerId id = 0;
            public long nextTick = 0;
            public long spanTicks = 0;
            public int callTimes = 0;
            public System.Action callFn;

            public int CompareTo(Item y)
            {
                int ret = nextTick.CompareTo(y.nextTick);
                if (0 != ret)
                    return ret;
                ret = id.CompareTo(y.id);
                return ret;
            }
        }

        TimerId m_lastId = 0;
        SortedSet<Item> m_items = new SortedSet<Item>();
        Dictionary<TimerId, Item> m_id2Item = new Dictionary<TimerId, Item>();

        public TimerId Add(System.Action cb, float delaySec, float spanSec, int callTimes)
        {
            if (null == cb)
                return 0;

            ++m_lastId;
            if (0 == m_lastId)
                ++m_lastId;

            Item item = new Item();
            item.id = m_lastId;
            item.callFn = cb;
            item.callTimes = callTimes;
            System.DateTime dt = app.datetimeModule.now.AddSeconds(delaySec);
            item.nextTick = dt.Ticks;
            item.spanTicks = 0;
            if (spanSec > 0)
            {
                item.spanTicks = (long)Math.Ceiling(TimeSpan.TicksPerSecond * spanSec);
                if (item.spanTicks <= 0)
                    item.spanTicks = 1;
            }
            m_id2Item.Add(item.id, item);
            m_items.Add(item);
            return m_lastId;
        }

        public void Remove(TimerId id)
        {
            Item item;
            if (m_id2Item.TryGetValue(id, out item))
            {
                m_items.RemoveWhere(x => x.id == id);
                m_id2Item.Remove(id);
            }
        }

        public void ClearAll()
        {
            m_id2Item.Clear();
            m_items.Clear();
        }

        protected override ERet OnStart()
        {
            ERet ret = base.OnStart();


            this.Add(() =>
            {
                app.logModule.LogDebug("Timer 1");
            }, 2.0f, 1.0f, 10);

            this.Add(() =>
            {
                app.logModule.LogDebug("Timer 2");
            }, 2.0f, 1.0f, -1);

            this.Add(() =>
            {
                app.logModule.LogDebug("Timer 3");
            }, 2.0f, 1.0f, 0);

            return ret;
        }

        protected override void OnFixedUpdate()
        {
            long nowTicks = app.datetimeModule.now.Ticks;
            Item minItem = new Item();
            Item endItem = new Item()
            {
                id = UInt64.MaxValue,
                nextTick = nowTicks
            };

            SortedSet<Item> hitItems = m_items.GetViewBetween(minItem, endItem);
            List<Item> toRemoveItems = new List<Item>();
            foreach (Item item in hitItems)
            {
                item.callFn();
                bool willRemove = item.callTimes >= 0 && item.callTimes <= 1;
                if (willRemove)
                {
                    toRemoveItems.Add(item);
                    continue;
                }
                if (item.callTimes > 0)
                    --item.callTimes;
                item.nextTick = nowTicks + item.spanTicks;
            }
            foreach (Item item in toRemoveItems)
            {
                this.Remove(item.id);
            }
        }
    }
}

