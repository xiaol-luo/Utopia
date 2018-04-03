#include "AutoHead.h"

int OK::CommonFunc(int param)
{
	return param;
}

void NoneSpaceClass::Test(int ti, float tf)
{

}

namespace OK
{
	int CommonIVal = 444;
	int OuterClass::siVal = 100;
	int OuterClass::TestStaticFun(int param)
	{
		return param;
	}
}