#include "stdafx.h"
#include "CGraphicD3D9.h"
#include "AlphaCommon/CAlphaWindow.h"
#include <iostream>
#include "CGraphicFactoryD3D9.h"
#pragma comment(lib, "d3d9.lib")

D3DFORMAT g_eTextureD3D9Format[eTF_Cnt] = 
{
	D3DFMT_DXT1,
	D3DFMT_DXT5,
	D3DFMT_R8G8B8,
	D3DFMT_A8R8G8B8,
	D3DFMT_R5G6B5,
	D3DFMT_A4R4G4B4,
	(D3DFORMAT)MAKEFOURCC('E', 'T', 'C', '2'),
	(D3DFORMAT)MAKEFOURCC('E', 'A', 'C', 'A'),
	D3DFMT_X8B8G8R8,
	D3DFMT_A8B8G8R8,
	(D3DFORMAT)MAKEFOURCC('5', '6', '5', 'R'),
	(D3DFORMAT)MAKEFOURCC('4', 'x', '4', 'R'),
	(D3DFORMAT)MAKEFOURCC('4', 'x', '4', 'N'),
	D3DFMT_A8,
	D3DFMT_V8U8,
	D3DFMT_R16F,
	D3DFMT_R32F,
	D3DFMT_A2R10G10B10,
	D3DFMT_G16R16,
	D3DFMT_G16R16F,
	D3DFMT_A16B16G16R16F,
	D3DFMT_G32R32F,
	D3DFMT_A32B32G32R32F,
	(D3DFORMAT)MAKEFOURCC('N', 'U', 'L', 'L'),
	D3DFMT_D16,
	D3DFMT_D24S8,
	(D3DFORMAT)MAKEFOURCC('I', 'N', 'T', 'Z')
};

CGraphicD3D9::CGraphicD3D9( CAlphaWindow* pWindow ):
	CGraphic(pWindow),
	m_pMainSwapChain(NULL),
	m_pD3D9(NULL),
	m_pDevice(NULL),
	m_pBackBuffer(NULL)
{
	m_pGraphicFactory = new CGraphicFactoryD3D9(this);
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

	return CGraphic::Create();
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
	D3DPRESENT_PARAMETERS param = m_D3D9Param;
	param.BackBufferHeight = 16;
	param.BackBufferWidth = 16;
	for (i = 0; i < 4; i ++)
	{
		result = m_pD3D9->CreateDevice(eAdapter, eDeviceType, m_pWnd->GetHandle(), 
			vectexType[i], &param, &m_pDevice);
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

	m_fHWVertexShaderVersion = (uint8)D3DSHADER_VERSION_MAJOR(m_Caps.VertexShaderVersion);
	m_fHWPixelShaderVersion = (uint8)D3DSHADER_VERSION_MAJOR(m_Caps.PixelShaderVersion);
	m_nMaxSupportRenderTargetCnt = m_Caps.NumSimultaneousRTs;

	return EnumSupportTextureFormat();
}

bool CGraphicD3D9::RenderBegin()
{
	HRESULT result = CheckDevice();
	if (FAILED(result))
	{
		if (result == D3DERR_DEVICENOTRESET)
		{
			D3DPRESENT_PARAMETERS param = m_D3D9Param;
			param.BackBufferHeight = 16;
			param.BackBufferWidth = 16;
			m_pDevice->Reset(&param);
		}
		return false;
	}
	result = m_pDevice->BeginScene();
	m_pDevice->ColorFill(m_pBackBuffer, 0, 0x000000ff);
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000ff, 1.0f, 0);
	return !FAILED(result);
}

void CGraphicD3D9::RenderEnd()
{
	m_pDevice->EndScene();
	m_pMainSwapChain->Present(0, 0, 0, 0, D3DPRESENT_DONOTWAIT);
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
	if (rect.right - rect.left != m_D3D9Param.BackBufferWidth || 
		rect.bottom - rect.top != m_D3D9Param.BackBufferHeight ||
		m_pMainSwapChain == NULL)
	{
		m_D3D9Param.BackBufferWidth = rect.right - rect.left;
		m_D3D9Param.BackBufferHeight = rect.bottom - rect.top;
		if (!CreateBackBuffer())
			return -1;
	}
	return D3D_OK;
}

bool CGraphicD3D9::CreateBackBuffer()
{
	D3DPRESENT_PARAMETERS param = m_D3D9Param;
	param.EnableAutoDepthStencil = false;
	HRESULT result = m_pDevice->CreateAdditionalSwapChain(&param, &m_pMainSwapChain);
	if (FAILED(result))
		return false;
	m_pMainSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer);
	m_pDevice->SetRenderTarget(0, m_pBackBuffer);
	return true;
}

void CGraphicD3D9::Destroy()
{
	CGraphic::Destroy();
	SAFE_RELEASE(m_pD3D9);
	SAFE_RELEASE(m_pDevice);
}

bool CGraphicD3D9::EnumSupportTextureFormat()
{
	memset (m_eSupportFormat, D3DFMT_UNKNOWN, sizeof(m_eSupportFormat));

	D3DDISPLAYMODE displayModel;
	if (m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayModel))
		return false;

	for (uint8 i = 0; i < eDT_Cnt; i ++)
	{
		if (m_pD3D9->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displayModel.Format, 0, D3DRTYPE_TEXTURE, g_eTextureD3D9Format[i]) == D3D_OK)
			m_eSupportFormat[i] = g_eTextureD3D9Format[i];
	}

	return (m_eSupportFormat[eTF_DXT1] && 
			m_eSupportFormat[eTF_DXT5] &&
			m_eSupportFormat[eTF_RBG24] && 
			m_eSupportFormat[eTF_ARGB32] &&
			m_eSupportFormat[eTF_R5G6B5]);

}

D3DFORMAT CGraphicD3D9::ToD3DFmt( ETextureFormat eFormat )
{
	if (eFormat >= eTF_Cnt)
		return D3DFMT_UNKNOWN;
	return g_eTextureD3D9Format[eFormat];
}

D3DFORMAT CGraphicD3D9::ToTextureFmt( ETextureFormat eFormat )
{
	if (eFormat >= eTF_Cnt)
		return D3DFMT_UNKNOWN;
	return m_eSupportFormat[eFormat];
}
