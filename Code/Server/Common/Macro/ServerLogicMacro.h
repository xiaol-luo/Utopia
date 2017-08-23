#pragma once
class ServerLogic;
extern ServerLogic *server_logic;

#define ServerLogicInstance server_logic
#define ModuleMgrInstance server_logic->GetModuleMgr()
