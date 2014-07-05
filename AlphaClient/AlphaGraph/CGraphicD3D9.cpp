#include "stdafx.h"
#include "CGraphicD3D9.h"
#include "AlphaCommon/CAlphaWindow.h"
#include "AlphaCommon/CAlphaCommonType.h"
#include <iostream>
#pragma comment(lib, "d3d9.lib")

CGraphicD3D9::CGraphicD3D9( CAlphaWindow* pWindow ):
	m_pWnd(pWindow)
{

}

CGraphicD3D9::~CGraphicD3D9()
{
	SAFE_RELEASE(m_pD3D9);
	SAFE_RELEASE(m_pDevice);
}

bool CGraphicD3D9::Create()
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	RECT rect;
	GetClientRect(m_pWnd->GetHandle(), &rect);
	m_D3D9Param.BackBufferWidth = rect.right - rect.left;
	m_D3D9Param.BackBufferHeight = rect.bottom - rect.top;
	m_D3D9Param.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_D3D9Param.BackBufferCount = 1;
	m_D3D9Param.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3D9Param.MultiSampleQuality = 0;
	m_D3D9Param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3D9Param.hDeviceWindow = m_pWnd->GetHandle();
	m_D3D9Param.Windowed = true;
	m_D3D9Param.EnableAutoDepthStencil = true;
	m_D3D9Param.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_D3D9Param.Flags = 0;
	m_D3D9Param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3D9Param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return CreateSuitableDevice();
}

bool CGraphicD3D9::CreateSuitableDevice()
{
	uint32 eAdapter = D3DADAPTER_DEFAULT;
	D3DDEVTYPE eDeviceType = D3DDEVTYPE_HAL;

	uint32 vectexType[4] = 
	{
		D3DCREATE_PUREDEVICE | D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
		D3DCREATE_PUREDEVICE | D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE
	};
	uint8 i;
	HRESULT result;
	for (i = 0; i < 4; i ++)
	{
		result = m_pD3D9->CreateDevice(eAdapter, eDeviceType, m_pWnd->GetHandle(), 
			vectexType[i], &m_D3D9Param, &m_pDevice);
		if (!FAILED(result))
			break;
	}
	if (i >= 4)
		return false;

	D3DDISPLAYMODE mode;
	result = m_pDevice->GetDisplayMode(eAdapter, &mode);
	if (FAILED(result))
		return false;

	result = m_pDevice->GetDeviceCaps(&m_Caps);
	if (FAILED(result))
		return false;


	return true;
}

bool CGraphicD3D9::RenderBegin()
{
	HRESULT result = CheckDevice();
	if (FAILED(result))
	{
		//if (result == D3DERR_DEVICELOST)
		return false;
	}
	result = m_pDevice->BeginScene();
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000ff, 1.0f, 0);
	return !FAILED(result);
}

void CGraphicD3D9::RenderEnd()
{
	m_pDevice->EndScene();
	m_pDevice->Present(0, 0, 0, 0);
}

IDirect3DDevice9* CGraphicD3D9::GetDevice()
{
	return m_pDevice;
}

HRESULT CGraphicD3D9::CheckDevice()
{
	HRESULT result = m_pDevice->TestCooperativeLevel();
	if (FAILED(result))
		return result;
	RECT rect = m_pWnd->GetClientRect();
	if (!rect.right || !rect.bottom)
		return -1;
	return D3D_OK;
}

bool CGraphicD3D9::CreateBackBuffer()
{
	m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	return true;
}
