#pragma once
#include "SceneObject.h"

namespace GameLogic
{
	class NavAgent;

	class MoveObject : public SceneObject
	{
	public:
		MoveObject(ESceneObjectType obj_type);
		virtual ~MoveObject();

	protected:
		NavAgent *m_navAgent = nullptr;
	};
}