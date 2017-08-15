#pragma once

#include "Modules/ModuleMgr.h"

enum EGameState
{
	EGameState_Free,
	EGameState_Init,
	EGameState_Awake,
	EGameState_Update,
	EGameState_Release,
	EGameState_Destroy,
	EGameState_Max,
};

class Game
{
public:
	Game();
	~Game();

	void SetParam(void *param) { m_param = param; }
	void Loop();
	void Quit();
	EGameState GetState() { return m_game_state; }

private:
	bool Init(void *param);
	bool Awake(void *param);
	void Update(void *param);
	void Realse(void *param);
	void Destroy(void *param);

	EGameState m_game_state = EGameState_Free;
	std::shared_ptr<ModuleMgr> m_module_mgr = nullptr;
	void * m_param;
	int m_ms_per_frame = 100;
};
