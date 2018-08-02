#pragma once

// #include "ServerLogics/ServerLogic.h"

class ServerLogic;
extern ServerLogic *server_logic;

#define G_ModuleMgr server_logic->GetModuleMgr()
#define G_Log server_logic->GetLog()
#define G_Net server_logic->GetNet()
#define G_NetAgent server_logic->GetNetAgent()
#define G_Timer server_logic->GetTimer()
#define G_Event server_logic->GetEvent()

