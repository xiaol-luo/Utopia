using System;
using System.Collections.Generic;

namespace Utopia
{
    public class TimerMgr
    {
        public const ulong INVALID_ID = 0;

        public delegate DateTime FnDateTime();
        FnDateTime m_fnDateTime;

        DateTime now { get { return m_fnDateTime(); } }

        public TimerMgr(FnDateTime fn)
        {
            m_fnDateTime = fn;
        }

        class Item
        {
            public ulong id = 0;
            public long nextTick = 0;
            public long spanTicks = 0;
            public int callTimes = 0;
            public System.Action callFn;
        }

        class ItemSortWay : IComparer<Item>
        {
            int IComparer<Item>.Compare(Item x, Item y)
            {
                int ret = x.nextTick.CompareTo(y.nextTick);
                if (0 != ret)
                    return ret;
                ret = x.id.CompareTo(y.id);
                return ret;
            }
        }

        SortedList<Item, Item> m_items = new SortedList<Item, Item>(new ItemSortWay());
        ulong m_lastId = 0;
        Dictionary<ulong, Item> m_id2Item = new Dictionary<ulong, Item>();

        public ulong Add(System.Action cb, float delaySec, int callTimes, float callSpanSec)
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
            System.DateTime dt = this.now.AddSeconds(delaySec);
            item.nextTick = dt.Ticks;
            item.spanTicks = 0;
            if (callSpanSec > 0)
            {
                item.spanTicks = (long)Math.Ceiling(TimeSpan.TicksPerSecond * callSpanSec);
                if (item.spanTicks <= 0)
                    item.spanTicks = 1;
            }
            m_id2Item.Add(item.id, item);
            m_items.Add(item, item);
            return m_lastId;
        }

        public ulong Add(System.Action cb, float delaySec)
        {
            ulong ret = this.Add(cb, delaySec, 1, 0);
            return ret;
        }

        public ulong Add(System.Action cb, int callTimes, float spanSec)
        {
            ulong ret = this.Add(cb, 0, callTimes, spanSec);
            return ret;
        }

        public void Remove(ulong id)
        {
            if (m_isCheckingTrigger)
            {
                m_waitRemoveTimerIds.Add(id);
                return;
            }

            Item item;
            if (m_id2Item.TryGetValue(id, out item))
            {
                m_items.Remove(item);
                m_id2Item.Remove(id);
            }
        }

        public void ClearAll()
        {
            if (m_isCheckingTrigger)
            {
                m_waitRemoveTimerIds.UnionWith(m_id2Item.Keys);
                return;
            }
            m_id2Item.Clear();
            m_items.Clear();
        }

        bool m_isCheckingTrigger = false;
        HashSet<ulong> m_waitRemoveTimerIds = new HashSet<ulong>();
        public void CheckTrigger()
        {
            m_isCheckingTrigger = true;

            long nowTicks = this.now.Ticks;
            Item minItem = new Item();
            Item endItem = new Item()
            {
                id = UInt64.MaxValue,
                nextTick = nowTicks
            };

            List<Item> hitItems = new List<Item>();
            foreach (Item item in m_items.Values)
            {
                if (item.nextTick > nowTicks)
                    break;
                hitItems.Add(item);
            }

            List<Item> toRemoveItems = new List<Item>();
            List<Item> toReAddItems = new List<Item>();
            foreach (Item item in hitItems)
            {
                m_items.Remove(item);
                item.callFn();

                bool willRemove = item.callTimes >= 0 && item.callTimes <= 1;
                if (willRemove)
                {
                    toRemoveItems.Add(item);
                }
                else
                {
                    if (item.callTimes > 0)
                        --item.callTimes;
                    item.nextTick = nowTicks + item.spanTicks;
                    toReAddItems.Add(item);
                }
            }
            foreach (Item item in toRemoveItems)
            {
                m_id2Item.Remove(item.id);
            }
            foreach (Item item in toReAddItems)
            {
                m_items.Add(item, item);
            }

            m_isCheckingTrigger = false;
            foreach (ulong id in m_waitRemoveTimerIds)
            {
                this.Remove(id);
            }
        }
    }
}

