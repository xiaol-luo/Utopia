#include "Common/Macro/MemoryPoolMacro.h"
#include "Common/Utils/GlobalMemoryMgr.h"

#include "GameLogic/GameLogicModule.h"
NewDelOperaImplement(GameLogicModule);

#include "GameLogic/Player/Player.h"
NewDelOperaImplement(GameLogic::Player);
#include "GameLogic/Player/PlayerMgr.h"
NewDelOperaImplement(GameLogic::PlayerMgr);
