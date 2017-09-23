#pragma once
#include "SceneObject.h"

namespace GameLogic
{
	class MoveObject : public SceneObject
	{
	public:
		MoveObject(ESceneObjectType obj_type);
		virtual ~MoveObject();
	};
}