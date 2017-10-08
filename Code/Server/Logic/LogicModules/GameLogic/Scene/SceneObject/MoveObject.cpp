#include "MoveObject.h"
#include "GameLogic/Scene/Navigation/NavAgent.h"

namespace GameLogic
{
	MoveObject::MoveObject(ESceneObjectType obj_type) : SceneObject(obj_type)
	{
		m_navAgent = new NavAgent();
	}

	MoveObject::~MoveObject()
	{

	}
}

