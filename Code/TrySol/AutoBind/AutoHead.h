#pragma once

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
		int TestOuterFun(InnerClass && param, int param2) { return 0; }
		static int TestStaticFun(int param);
	};
	
	extern int CommonFunc(int param);
	extern int CommonIVal;
}

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