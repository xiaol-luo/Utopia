#pragma once

#include "MoveObject.h"

namespace GameLogic
{
	class Player;
	class Scene;

	class Hero : public MoveObject
	{
	public:
		Hero();
		virtual ~Hero();

	public:
		void SetPlayer(Player *player);
		Player * GetPlayer() { return m_Player; }
	private:
		Player *m_Player = nullptr;

		/*
	protected:
		void OnMoveAgentStateChange(EMoveAgentState old_val);
		void OnPosChange(const Vector3 &old_val);
		void OnVelocityChange(const Vector3 &old_val);
		void OnSpeedChange(float old_val);
		void OnRotationChange(float old_val);
		void OnRadiusChange(float old_val);
		*/
	};
}
