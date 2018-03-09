#pragma once

#include "ServerLogics/ServerLogic.h"
extern ServerLogic *server_logic;

#define GlobalServerLogic server_logic
#define GlobalModuleMgr server_logic->GetModuleMgr()
#define GlobalLog GlobalServerLogic->GetLogModule()

