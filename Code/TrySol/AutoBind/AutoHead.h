#pragma once

#include <string>

namespace OK
{
	class Test;
	class Test
	{ 
	public:
		int a;
	};
	class Base {};


	class OuterClass : public Base
	{
	public:
		struct InnerClass
		{
			int ival = 0;
			const int * TestInnerFunc(const int param) { return 0; }
		};

	public:
		OuterClass() {}

		InnerClass inClass;
		const float fval = 2;
		static int siVal;
		int TestOuterFun(InnerClass & param, int param2);
		int TestOverload(int param2);
		int TestOverload(int param2, float p2);
		static int TestStaticFun(int param);
		static int TestStaticFun(int param, float p2);
		static int TestStaticFun2(int param, float p2);

	};
	
	extern int CommonFunc(int param);
	extern int CommonIVal;
	void Test3(int a);
	void Test3(int a, float b);
}

void TestStr(std::string xxx);

class NoneSpaceClass
{
public:
	int iVal;
	void Test(int ti, float tf);
};

enum TryEnum
{
	E1,
	E2 = 3,
	E3 = 4,
	E4,
};