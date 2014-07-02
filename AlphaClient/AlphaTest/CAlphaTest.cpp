// AlphaTest.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CAlphaTest.h"
#include "AlphaCommon/CAlphaWindow.h"
#include "AlphaGraph/CGraphicD3D9.h"
#include <Mmsystem.h>
#pragma comment( lib,"winmm.lib" )

CAlphaWindow *g_pWindow;
CGraphicD3D9 *g_pGraph;
bool init()
{
	g_pWindow = new CAlphaWindow;
	g_pWindow->Initialize(NULL, 800, 600, "MyTestTitle", 0);
	g_pGraph = new CGraphicD3D9(g_pWindow);
	return g_pGraph->Create();
}

void destroy()
{
	SAFE_DELETE(g_pGraph);
	SAFE_DELETE(g_pWindow);
}

int main()
{
	init();

	static float lastTime = (float)timeGetTime();
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while(msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			float currTime = (float)timeGetTime();
			float deltTime = (currTime - lastTime) * 0.001f;
			g_pGraph->Update(deltTime);
			lastTime = currTime;
		}
	}

	destroy();
	return 0;
}