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
#include "AlphaGraph/CRenderStateMgr.h"
#pragma comment( lib,"winmm.lib" )

CAlphaWindow* g_pWindow;
CGraphicD3D9* g_pGraphic;
CModel* g_pCube;
CModel* g_pSphere;
CModel* g_pPlane;
CCamera* g_pCamera;
CCamera* g_pCamera2;
CTexture* g_pRenderTarget;
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
	g_pCamera->SetPosition(new D3DXVECTOR3(0, 0, -5));
	g_pCamera->SetProject(D3DX_PI * 0.5f, g_pWindow->GetClientRect().right * 1.0f / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);

	g_pCamera2 = new CCamera(CCamera::ECT_AIRCRAFT);
	g_pCamera2->SetPosition(new D3DXVECTOR3(0, 0, -5));
	g_pCamera2->SetProject(D3DX_PI * 0.5f, g_pWindow->GetClientRect().right * 1.0f / g_pWindow->GetClientRect().bottom, 1.0f, 1000.0f);
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
	g_pRenderTarget = g_pGraphic->CreateRenderTarget(g_pWindow->GetClientRect().right, g_pWindow->GetClientRect().bottom, eTF_ARGB32, 1, eTF_D24S8);
}

void destroy()
{
	SAFE_DELETE(g_pGraphic);
	SAFE_DELETE(g_pWindow);
}

void renderMainScene(SMaterial& material)
{
	material.m_pShader->SetParamData("textureSampler", g_pCube->GetTexture(), sizeof(CTexture), eSDT_Texture);
	g_pGraphic->DrawPrimitive(material, nullptr, 0, ePT_TriangleList, g_pCube->GetVertexCount(), g_pCube->GetVertexCount() / 3,
		g_pCube->GetVertexType(), g_pCube->GetVertexSize(), (const void*)g_pCube->GetVertexBuffer(), nullptr);

	CMatrix sphereWorld;
	sphereWorld[3][0] += 3;
	material.m_pShader->SetParamData("textureSampler", g_pSphere->GetTexture(), sizeof(CTexture), eSDT_Texture);
	g_pGraphic->DrawPrimitive(material, &sphereWorld, 1, ePT_TriangleList, g_pSphere->GetVertexCount(), g_pSphere->GetVertexCount() / 3,
		g_pSphere->GetVertexType(), g_pSphere->GetVertexSize(), (const void*)g_pSphere->GetVertexBuffer(), nullptr);

	CMatrix planeWorld;
	planeWorld[3][0] += 2;
	planeWorld[3][1] -= 1;
	material.m_pShader->SetParamData("textureSampler", g_pPlane->GetTexture(), sizeof(CTexture), eSDT_Texture);
	g_pGraphic->DrawPrimitive(material, &planeWorld, 1, ePT_TriangleList, g_pPlane->GetVertexCount(), g_pPlane->GetVertexCount() / 3,
		g_pPlane->GetVertexType(), g_pPlane->GetVertexSize(), (const void*)g_pPlane->GetVertexBuffer(), nullptr);
}

struct SVertexType2
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
};

void renderTexture()
{
	SMaterial material;
	material.m_pShader = g_pGraphic->CreateShaderFromFile("F://GameProject/Alpha/AlphaClient/AlphaShader/texture.fx");
	material.m_pShader->SetParamData("textureSampler", g_pRenderTarget, sizeof(CTexture), eSDT_Texture);
	SVertexElem arrElem[] =
	{
		0, eDT_3Float, eDU_Position,
		12, eDT_2Float, eDU_Texcoord0,
	};
	uint16 nVertexFormat = g_pGraphic->CreateVertexFormat(arrElem, ELEMENT_CNT(arrElem));
	SVertexType2 v[4];
	v[0].position = D3DXVECTOR3(-7.0 / 6, -1, -3);
	v[0].texture = D3DXVECTOR2(0, 1);
	v[1].position = D3DXVECTOR3(-7.0 / 6, 1, -3);
	v[1].texture = D3DXVECTOR2(0, 0);
	v[2].position = D3DXVECTOR3(7.0 / 6, -1, -3);
	v[2].texture = D3DXVECTOR2(1, 1);
	v[3].position = D3DXVECTOR3(7.0 / 6, 1, -3);
	v[3].texture = D3DXVECTOR2(1, 0);
	g_pGraphic->DrawPrimitive(material, nullptr, 0, ePT_TriangleStrip, 4, 2, nVertexFormat, sizeof(SVertexType2), (const void*)v, nullptr);
}

struct SVertexType3
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 color;
};


void renderColor()
{
	SMaterial material;
	material.m_pShader = g_pGraphic->CreateShaderFromFile("F://GameProject/Alpha/AlphaClient/AlphaShader/color.fx");
	SVertexElem arrElem[] =
	{
		0, eDT_3Float, eDU_Position,
		12, eDT_3Float, eDU_Color0,
	};
	uint16 nVertexFormat = g_pGraphic->CreateVertexFormat(arrElem, ELEMENT_CNT(arrElem));
	SVertexType3 v[4];
	v[0].position = D3DXVECTOR3(-1, -1, 0);
	v[0].color = D3DXVECTOR3(0, 0, 0);
	v[1].position = D3DXVECTOR3(-1, 1, 0);
	v[1].color = D3DXVECTOR3(0, 255, 0);
	v[2].position = D3DXVECTOR3(1, -1, 0);
	v[2].color = D3DXVECTOR3(255, 0, 0);
	v[3].position = D3DXVECTOR3(1, 1, 0);
	v[3].color = D3DXVECTOR3(0, 0, 255);
	g_pGraphic->DrawPrimitive(material, nullptr, 0, ePT_TriangleStrip, 4, 2, nVertexFormat, sizeof(SVertexType2), (const void*)v, nullptr);

}

void updateFrame(uint32 nDeltaTime)
{
	CCamera* pCamera;
	if (::GetAsyncKeyState('P') & 0x8000f)
		pCamera = g_pCamera;
	else
		pCamera = g_pCamera2;

	float fDeltaTime = nDeltaTime / 1000.0f;
	if (::GetAsyncKeyState('W') & 0x8000f)
		pCamera->walk(4 * fDeltaTime);
	if (::GetAsyncKeyState('S') & 0x8000f)
		pCamera->walk(-4 * fDeltaTime);
	if (::GetAsyncKeyState('A') & 0x8000f)
		pCamera->strafe(-4 * fDeltaTime);
	if (::GetAsyncKeyState('D') & 0x8000f)
		pCamera->strafe(4 * fDeltaTime);
	if (::GetAsyncKeyState('R') & 0x8000f)
		pCamera->fly(4 * fDeltaTime);
	if (::GetAsyncKeyState('F') & 0x8000f)
		pCamera->fly(-4 * fDeltaTime);
	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		pCamera->pitch(fDeltaTime);
	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		pCamera->pitch(-1.0f * fDeltaTime);
	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		pCamera->yaw(fDeltaTime);
	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		pCamera->yaw(-1.0f * fDeltaTime);
	if (::GetAsyncKeyState('N') & 0x8000f)
		pCamera->roll(fDeltaTime);
	if (::GetAsyncKeyState('M') & 0x8000f)
		pCamera->roll(-1.0f * fDeltaTime);

	if (g_pGraphic->RenderBegin())
	{
		/*		
		g_pGraphic->PushEnvir();
 		g_pGraphic->SetView(g_pCamera2->GetView());
 		g_pGraphic->SetProj(g_pCamera2->GetProject());
		g_pGraphic->SetRenderTarget(g_pRenderTarget, g_pGraphic->GetMainRenderTarget());
 		renderMainScene("F://GameProject/Alpha/AlphaClient/AlphaShader/normal.fx");
		g_pGraphic->ClearRenderTarget(false, true, true, 0x00000000);
		g_pGraphic->PopEnvir();

		g_pGraphic->SetView(g_pCamera->GetView());
		g_pGraphic->SetProj(g_pCamera->GetProject());
		g_pGraphic->SetRenderTarget(nullptr, nullptr);
		SMaterial material;
		material.m_pShader = g_pGraphic->CreateShaderFromFile("F://GameProject/Alpha/AlphaClient/AlphaShader/normal.fx");
		material.m_pShader->SetParamData("textureSampler", g_pRenderTarget, sizeof(CTexture), eSDT_Texture);

		g_pGraphic->DrawPrimitive(material, nullptr, 0, ePT_TriangleList, g_pCube->GetVertexCount(), g_pCube->GetVertexCount() / 3,
			g_pCube->GetVertexType(), g_pCube->GetVertexSize(), (const void*)g_pCube->GetVertexBuffer(), nullptr);
		*/
		/*	
		g_pGraphic->SetView(g_pCamera->GetView());
		g_pGraphic->SetProj(g_pCamera->GetProject());
		renderMainScene("F://GameProject/Alpha/AlphaClient/AlphaShader/normal.fx");

		CMatrix sphereWorld;
		sphereWorld[3][0] += 3;
		SMaterial material;
		material.m_pShader = g_pGraphic->CreateShaderFromFile("F://GameProject/Alpha/AlphaClient/AlphaShader/outline.fx");
		material.m_nCullType = eMCT_CW;
		g_pGraphic->DrawPrimitive(material, &sphereWorld, 1, ePT_TriangleList, g_pSphere->GetVertexCount(), g_pSphere->GetVertexCount() / 3,
			g_pSphere->GetVertexType(), g_pSphere->GetVertexSize(), (const void*)g_pSphere->GetVertexBuffer(), nullptr);
		*/
		g_pGraphic->SetAmbient(CVector4f(0.3f, 0.3f, 0.3f, 1.0f));
		g_pGraphic->SetDiffuse(CVector4f(1.0f, 1.0f, 1.0f, 1.0f));

		g_pGraphic->PushEnvir();
		g_pGraphic->SetView(g_pCamera->GetView());
		g_pGraphic->SetProj(g_pCamera->GetProject());
		g_pGraphic->SetRenderTarget(g_pRenderTarget, g_pGraphic->GetMainRenderTarget());
		SMaterial material;
		material.m_pShader = g_pGraphic->CreateShaderFromFile("F://GameProject/Alpha/AlphaClient/AlphaShader/depth.fx");
		renderMainScene(material);
		g_pGraphic->ClearRenderTarget(false, true, true, 0x00000000);
		g_pGraphic->PopEnvir();

		g_pGraphic->SetView(g_pCamera2->GetView());
		g_pGraphic->SetProj(g_pCamera2->GetProject());
		g_pGraphic->SetRenderTarget(nullptr, nullptr);
		SMaterial material2;
		material2.m_pShader = g_pGraphic->CreateShaderFromFile("F://GameProject/Alpha/AlphaClient/AlphaShader/shadow.fx");
		material2.m_pShader->SetParamData("depthMapSampler", g_pRenderTarget, sizeof(CTexture), eSDT_Texture);
		material2.m_pShader->SetParamData("lightViewMatrix", &g_pCamera->GetView(), sizeof(CMatrix), eSDT_Matrix);
		material2.m_pShader->SetParamData("lightProjectionMatrix", &g_pCamera->GetProject(), sizeof(CMatrix), eSDT_Matrix);
		CVector4f pos(*(CVector3f*)g_pCamera->GetPosition(), 0);
		material2.m_pShader->SetParamData("lightPos", &pos, sizeof(CVector4f), eSDT_4Float);
		renderMainScene(material2);
// 		renderTexture();
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