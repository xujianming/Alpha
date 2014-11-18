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
		D3DXVECTOR3 position(0, 0, -7);
		D3DXVECTOR3 target(0, 0, 0);
		D3DXVECTOR3 up(0, 1, 0);

		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
	//	g_pGraphic->GetDevice()->SetTransform(D3DTS_WORLD, &world);

		D3DXMATRIX view;
		D3DXMatrixLookAtLH(&view, &position, &target, &up);
	//	g_pGraphic->GetDevice()->SetTransform(D3DTS_VIEW, &view);
		g_pGraphic->SetView(*(CMatrix*)&view);

		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, g_pWindow->GetClientRect().right / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);
	//	g_pGraphic->GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);
		g_pGraphic->SetProj(*(CMatrix*)&proj);

		CVector3f v[3];
		v[0] = CVector3f(1, 0, 0);
		v[1] = CVector3f(-1, 0, 0);
		v[2] = CVector3f(0, 1, 0);
		uint16 index[3];
		index[0] = 0;
		index[1] = 1; 
		index[2] = 2;
		SVertexElem arrElem[] = 
		{
			0, eSDT_4Float, eDU_Position
		};
		uint16 fmt = g_pGraphic->CreateVertexFormat(arrElem, 1);

		SMaterial material;
		material.m_pShader = g_pGraphic->CreateShaderFromFile("F://MyProject/Alpha/AlphaClient/AlphaShader/texture.fx");
		material.m_pShader->SetParamData("textureSampler", g_pModel->GetTexture(), INVALID_32BIT, eSDT_Texture);
		
	//	g_pGraphic->DrawPrimitive(material, ePT_TriangleList, g_pModel->GetVertexCount(), g_pModel->GetVertexCount() - 2,
	//		g_pModel->GetVertexType(), sizeof(SVertexType), (const void*)g_pModel->GetVertexBuffer(), (const void*)g_pModel->GetIndexBuffer());

		g_pGraphic->DrawPrimitive(material, ePT_TriangleList, 3, 1, fmt, sizeof(CVector3f), v, index);

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
		updateFrame(uint32(nCurTime - nPreTime));
		nPreTime = nCurTime;
	}
	destroy();
	return 0;
}