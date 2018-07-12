using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utopia.Event
{
    class AppEvent
    {
        public const string GameToQuit = "GameToQuit";
        public const string GameStarted = "GameStarted";
        public const string UIPanelMgr_LoadPanelProxyResourceFail = "LoadPanelProxyResourceFail";
        public const string UIPanelMgr_BecomeReady = "UIPanelMgr_BecomeReady";
    }
}
