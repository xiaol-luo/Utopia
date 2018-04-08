#include "AutoHead.h"
#include "AutoHeadOther.h"

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

	int OuterClass::TestOuterFun(InnerClass & param, int param2)
	{
		return param.ival + param2;
	}

	int OuterClass::TestStaticFun(int param)
	{
		return param;
	}
	int OuterClass::TestStaticFun(int param, float p2)
	{
		return param;
	}
	int OuterClass::TestStaticFun2(int param, float p2)
	{
		return param;
	}

	int OuterClass::TestOverload(int param2)
	{
		return param2;
	}
	void OuterClass::TestOverload(int param2) const
	{
		
	}
	int OuterClass::TestOverload(int param2, float p2)
	{
		return param2 + p2;
	}
}

void TestStr(std::string xxx)
{

}

void TestStr2(std::string xxx)
{

}

void OK::Test3(int a)
{

}

void OK::Test3(int a, float b)
{

}

void OK::Test2(int a)
{

}

