#include "stdafx.h"
#include "CGraphicD3D9.h"
#include "CAlphaWindow.h"
#include "CAlphaCommonType.h"

CGraphicD3D9::CGraphicD3D9( CAlphaWindow* pWindow ):
	m_pWnd(pWindow)
{

}

CGraphicD3D9::~CGraphicD3D9()
{

}

void CGraphicD3D9::Create()
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	LPRECT rect;
	GetClientRect(m_pWnd->GetHandle(), rect);
	m_D3D9Param.BackBufferWidth = rect->right - rect->left;
	m_D3D9Param.BackBufferHeight = rect->bottom - rect->top;
	m_D3D9Param.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_D3D9Param.BackBufferCount = 1;
	m_D3D9Param.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3D9Param.MultiSampleQuality = 0;
	m_D3D9Param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3D9Param.hDeviceWindow = m_pWnd->GetHandle();
	m_D3D9Param.Windowed = false;
	m_D3D9Param.EnableAutoDepthStencil = true;
	m_D3D9Param.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_D3D9Param.Flags = 0;
	m_D3D9Param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3D9Param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	CreateSuitableDevice();
}

bool CGraphicD3D9::CreateSuitableDevice()
{
	uint32 eAdapter = D3DADAPTER_DEFAULT;
	uint32 eDeviceType = D3DDEVTYPE_HAL;

	HRESULT result = m_pD3D9->GetDeviceCaps(eAdapter, eDeviceType, m_pCaps);
	if (FAILED(result))
		return false;
	if (m_pCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		m_eVertexProcessType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		m_eVertexProcessType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	result = m_pD3D9->CreateDevice(eAdapter, eDeviceType, m_pWnd->GetHandle(), 
		m_eVertexProcessType, &m_D3D9Param, &m_pDevice);
	if (FAILED(result))
	{

	}

}

void CGraphicD3D9::RenderBegin()
{

}

void CGraphicD3D9::RenderEnd()
{

}

