#include "GeometryDefine.h"
#include <float.h>

const Axis2 Axis2::x_axis = Axis2(Vector2(0, 0), Vector2(1, 0));
const Axis2 Axis2::y_axis = Axis2(Vector2(0, 0), Vector2(0, 1));

bool Axis2::IsValid() const
{
	return direction.SqrMagnitude() >= FLT_EPSILON;
}

