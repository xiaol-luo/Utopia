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
	int OuterClass::TestStaticFun(int param)
	{
		return param;
	}

	/*
	int OuterClass::TestStaticFun(int param, float p2)
	{
		return param;
	}
	*/
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

