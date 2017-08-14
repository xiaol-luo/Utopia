#include <stdio.h>
#include "Utils/ConfigUtil.h"

int main(int argc, char **argv)
{
	printf("hello world");

	int a = 0;
	ConfigUtil::Str2BaseValue("123", a);
}