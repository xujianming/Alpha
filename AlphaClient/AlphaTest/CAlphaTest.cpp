// AlphaTest.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CAlphaTest.h"
#include "AlphaCommon/CAlphaWindow.h"
#include "AlphaGraph/CRenderer.h"
#include "AlphaGraph/CGraphic.h"

#include <Mmsystem.h>
#pragma comment( lib,"winmm.lib" )

CAlphaWindow *g_pWindow;
CRenderer	 *g_pRenderer;
void init()
{
	g_pWindow = new CAlphaWindow;
	g_pWindow->Initialize(NULL, 800, 600, "MyTestTitle", 0);
	g_pRenderer = new CRenderer;
	g_pRenderer->Initialize(g_pWindow);
	g_pRenderer->GetGraphic()->CreateShaderFromFile("../AlphaShader/shadow.fx", false);
}

void destroy()
{
	SAFE_DELETE(g_pRenderer);
	SAFE_DELETE(g_pWindow);
}

int main()
{
	init();
	while (g_pWindow->Messagepump() >= 0)
	{
		g_pRenderer->EnterOneFrame();
	}
	destroy();
	return 0;
}