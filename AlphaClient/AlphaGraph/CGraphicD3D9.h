#pragma once

#include "AlphaCommon/AlphaCommonType.h"
#include "CGraphic.h"
#include <d3d9.h>

class CAlphaWindow;


class CGraphicD3D9: public CGraphic
{
public:
	CGraphicD3D9(CAlphaWindow *pWindow);

	~CGraphicD3D9();

	bool Create();

	bool RenderBegin();

	void RenderEnd();

	IDirect3DDevice9* GetDevice();

	HRESULT CheckDevice();

	bool CreateBackBuffer();

	void Destroy();

	D3DFORMAT ToD3DFmt(ETextureFormat eFormat);

	D3DFORMAT ToTextureFmt(ETextureFormat eFormat);

	ETextureFormat FromD3DFmt(D3DFORMAT format);
	
	IDirect3DSurface9* GetBackBuffer() { return m_pBackBuffer; }

protected:
	bool CreateSuitableDevice();

	bool EnumSupportTextureFormat();

	IDirect3D9* m_pD3D9;

	IDirect3DDevice9* m_pDevice;

	D3DCAPS9 m_Caps;

	D3DPRESENT_PARAMETERS m_D3D9Param;

	IDirect3DSurface9* m_pBackBuffer;

	IDirect3DSwapChain9* m_pMainSwapChain;

	D3DFORMAT m_eSupportFormat[eTF_Cnt];
};