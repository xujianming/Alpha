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
CModel* g_pCube;
CModel* g_pSphere;
CModel* g_pPlane;
CCamera* g_pCamera;

void init()
{
	g_pWindow = new CAlphaWindow;
	g_pWindow->Initialize(NULL, 800, 600, "MyTestTitle", 0);
	g_pGraphic = new CGraphicD3D9(g_pWindow);
	g_pGraphic->Create();
	g_pCube = new CModel(g_pGraphic);
	g_pSphere = new CModel(g_pGraphic);
	g_pPlane = new CModel(g_pGraphic);
	g_pCamera = new CCamera(CCamera::ECT_AIRCRAFT);
	g_pCamera->SetPosition(new D3DXVECTOR3(0, 1, -5));
	g_pCamera->SetProject(D3DX_PI * 0.5f, g_pWindow->GetClientRect().right * 1.0f / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);
	bool result = g_pCube->Initialize("../data/cube.txt", "../data/wall01.dds");
	if(!result)
	{
		MessageBox(g_pWindow->GetHandle(), L"Could not initialize the model object.", L"Error", MB_OK);
		return;
	}
	result = g_pSphere->Initialize("../data/sphere.txt", "../data/seafloor.dds");
	if(!result)
	{
		MessageBox(g_pWindow->GetHandle(), L"Could not initialize the model object.", L"Error", MB_OK);
		return;
	}
	result = g_pPlane->Initialize("../data/plane01.txt", "../data/metal001.dds");
	if (!result)
	{
		MessageBox(g_pWindow->GetHandle(), L"Could not initialize the model object.", L"Error", MB_OK);
		return;
	}
	g_pGraphic->AddLight(SLight());
	g_pGraphic->SetAmbient(CVector4f(0.3, 0.3, 0.3, 1));
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

		//D3DXMATRIX view;
		//D3DXMatrixLookAtLH(&view, &position, &target, &up);
		//g_pGraphic->GetDevice()->SetTransform(D3DTS_VIEW, &view);
		
		CMatrix view;
		g_pCamera->GetViewMatrix(&view);
		g_pGraphic->SetView(view);

		//D3DXMATRIX proj;
		//D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, g_pWindow->GetClientRect().right / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);
		//g_pGraphic->GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);
		g_pGraphic->SetProj(g_pCamera->GetProject());

		SMaterial material;
		material.m_pShader = g_pGraphic->CreateShaderFromFile("F://MyProject/Alpha/AlphaClient/AlphaShader/texture.fx");
		material.m_pShader->SetParamData("textureSampler", g_pCube->GetTexture(), sizeof(CTexture), eSDT_Texture);
		
		g_pGraphic->DrawPrimitive(material, nullptr, 0, ePT_TriangleList, g_pCube->GetVertexCount(), g_pCube->GetVertexCount() / 3,
			g_pCube->GetVertexType(), g_pCube->GetVertexSize(), (const void*)g_pCube->GetVertexBuffer(), nullptr);

		CMatrix sphereWorld;
		sphereWorld[3][0] += 3;
		material.m_pShader->SetParamData("textureSampler", g_pSphere->GetTexture(), sizeof(CTexture), eSDT_Texture);
		g_pGraphic->DrawPrimitive(material, &sphereWorld, 1, ePT_TriangleList, g_pSphere->GetVertexCount(), g_pSphere->GetVertexCount() / 3,
			g_pSphere->GetVertexType(), g_pSphere->GetVertexSize(), (const void*)g_pSphere->GetVertexBuffer(), nullptr);

		CMatrix planeWorld;
		planeWorld[3][1] -= 2;
		material.m_pShader->SetParamData("textureSampler", g_pPlane->GetTexture(), sizeof(CTexture), eSDT_Texture);
		g_pGraphic->DrawPrimitive(material, &planeWorld, 1, ePT_TriangleList, g_pPlane->GetVertexCount(), g_pPlane->GetVertexCount() / 3,
			g_pPlane->GetVertexType(), g_pPlane->GetVertexSize(), (const void*)g_pPlane->GetVertexBuffer(), nullptr);

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