#pragma once

#include "Modules/Timer/ITimerModule.h"

enum EGameState
{
	EGameState_Free,
	EGameState_Awake,
	EGameState_Run,
	EGameState_Quiting,
	EGameState_Quited,
	EGameState_Max,
};

class Game
{
public:
	Game();
	~Game();

	bool Init(void *param);
	bool Awake(void *param);
	void Update(void *param);
	void Realse(void *param);

	void Quit();
	void Terminal();

private:
	EGameState m_game_state = EGameState_Free;
};
