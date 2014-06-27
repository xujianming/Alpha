// AlphaTest.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CAlphaTest.h"
#include "AlphaCommon/CAlphaWindow.h"
CAlphaWindow window;

void init()
{
	window.Initialize(NULL, 800, 600, "MyTestTitle", 0);
}

int main()
{
	init();
	return 0;
}