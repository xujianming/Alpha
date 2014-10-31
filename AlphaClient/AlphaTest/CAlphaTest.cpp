// AlphaTest.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CAlphaTest.h"
#include "AlphaCommon/CAlphaWindow.h"
#include "AlphaGraph/CRenderer.h"
#include "AlphaGraph/CGraphicD3D9.h"
#include "AlphaGraph/CModel.h"
#include "AlphaGraph/CShader.h"
#include <ctime>
#include <Mmsystem.h>
#pragma comment( lib,"winmm.lib" )

CAlphaWindow* g_pWindow;
CGraphicD3D9* g_pGraphic;
CModel* g_pModel;
void init()
{
	g_pWindow = new CAlphaWindow;
	g_pWindow->Initialize(NULL, 800, 600, "MyTestTitle", 0);
	g_pGraphic = new CGraphicD3D9(g_pWindow);
	g_pGraphic->Create();
	g_pModel = new CModel(g_pGraphic);
	bool result = g_pModel->Initialize("../data/cube.txt", "../data/seafloor.dds");
	if(!result)
	{
		MessageBox(g_pWindow->GetHandle(), L"Could not initialize the model object.", L"Error", MB_OK);
		return;
	}
}

void destroy()
{
	SAFE_DELETE(g_pGraphic);
	SAFE_DELETE(g_pWindow);
}

void updateFrame(uint32 nDeltaTime)
{

	if (g_pGraphic->RenderBegin())
	{
		SMaterial material;
		material.m_pShader = g_pGraphic->CreateShaderFromFile("../shadow.fx");
		g_pGraphic->DrawPrimitive(material, ePT_TriangleList, g_pModel->GetVertexCount(), g_pModel->GetVertexCount() - 2,
			g_pModel->GetVertexType(), sizeof(ModelType), (const void*)g_pModel->GetVertexBuffer(), (const void* )g_pModel->GetIndexBuffer());

		g_pGraphic->RenderEnd();
	}
}

int main()
{
	init();
	time_t nPreTime;
	time(&nPreTime);
	while (g_pWindow->Messagepump() >= 0)
	{
		time_t nCurTime;
		time(&nCurTime);
		updateFrame(nCurTime - nPreTime);
		nPreTime = nCurTime;
	}
	destroy();
	return 0;
}