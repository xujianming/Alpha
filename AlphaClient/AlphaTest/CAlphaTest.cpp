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
#include "AlphaGraph/CCamera.h"
#pragma comment( lib,"winmm.lib" )

CAlphaWindow* g_pWindow;
CGraphicD3D9* g_pGraphic;
CModel* g_pModel;
CCamera* g_pCamera;
void init()
{
	g_pWindow = new CAlphaWindow;
	g_pWindow->Initialize(NULL, 800, 600, "MyTestTitle", 0);
	g_pGraphic = new CGraphicD3D9(g_pWindow);
	g_pGraphic->Create();
	g_pModel = new CModel(g_pGraphic);
	g_pCamera = new CCamera(CCamera::ECT_AIRCRAFT);
	g_pCamera->SetPosition(new D3DXVECTOR3(0, 1, -5));
	g_pCamera->SetProject(D3DX_PI * 0.5f, g_pWindow->GetClientRect().right * 1.0f / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);
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
	float fDeltaTime = nDeltaTime / 1000.0f;
	if (::GetAsyncKeyState('W') & 0x8000f)
		g_pCamera->walk(4 * fDeltaTime);
	if (::GetAsyncKeyState('S') & 0x8000f)
		g_pCamera->walk(-4 * fDeltaTime);
	if (::GetAsyncKeyState('A') & 0x8000f)
		g_pCamera->strafe(-4 * fDeltaTime);
	if (::GetAsyncKeyState('D') & 0x8000f)
		g_pCamera->strafe(4 * fDeltaTime);
	if (::GetAsyncKeyState('R') & 0x8000f)
		g_pCamera->fly(4 * fDeltaTime);
	if (::GetAsyncKeyState('F') & 0x8000f)
		g_pCamera->fly(-4 * fDeltaTime);
	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		g_pCamera->pitch(fDeltaTime);
	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		g_pCamera->pitch(-1.0f * fDeltaTime);
	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		g_pCamera->yaw(fDeltaTime);
	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		g_pCamera->yaw(-1.0f * fDeltaTime);
	if (::GetAsyncKeyState('N') & 0x8000f)
		g_pCamera->roll(fDeltaTime);
	if (::GetAsyncKeyState('M') & 0x8000f)
		g_pCamera->roll(-1.0f * fDeltaTime);

	if (g_pGraphic->RenderBegin())
	{
		D3DXVECTOR3 position(0, 0, -5);
		D3DXVECTOR3 target(0, 0, 0);
		D3DXVECTOR3 up(0, 1, 0);

		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		g_pGraphic->GetDevice()->SetTransform(D3DTS_WORLD, &world);

		D3DXMATRIX view;
		D3DXMatrixLookAtLH(&view, &position, &target, &up);
		g_pGraphic->GetDevice()->SetTransform(D3DTS_VIEW, &view);
		

		D3DXMATRIX view2;
		g_pCamera->GetViewMatrix(&view2);
		g_pGraphic->SetView(*(CMatrix*)&view2);


		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, g_pWindow->GetClientRect().right / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);
		g_pGraphic->GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);

		g_pGraphic->SetProj(g_pCamera->GetProject());

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
		material.m_pShader->SetParamData("textureSampler", g_pModel->GetTexture(), sizeof(CTexture), eSDT_Texture);
		
		g_pGraphic->DrawPrimitive(material, ePT_TriangleList, g_pModel->GetVertexCount(), g_pModel->GetVertexCount() - 2,
			g_pModel->GetVertexType(), sizeof(SVertexType), (const void*)g_pModel->GetVertexBuffer(), (const void*)g_pModel->GetIndexBuffer());

	//	g_pGraphic->DrawPrimitive(material, ePT_TriangleList, 3, 1, fmt, sizeof(CVector3f), v, index);

		g_pGraphic->RenderEnd();
	}
}

int main()
{
	init();
	clock_t nPreTime = clock();
	while (g_pWindow->Messagepump() >= 0)
	{
		clock_t nCurTime = clock();
		updateFrame(uint32(nCurTime - nPreTime));
		nPreTime = nCurTime;
	}
	destroy();
	return 0;
}