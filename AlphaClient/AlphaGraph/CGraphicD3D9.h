#pragma once

#include <d3d9.h>

class CAlphaWindow;
class CGraphicD3D9
{
public:
	CGraphicD3D9(CAlphaWindow *pWindow);
	~CGraphicD3D9();

	void Create();
	void RenderBegin();
	void RenderEnd();

protected:
	bool CreateSuitableDevice();
	CAlphaWindow* m_pWnd;
	IDirect3D9* m_pD3D9;
	IDirect3DDevice9* m_pDevice;
	D3DCAPS9* m_pCaps;
	D3DPRESENT_PARAMETERS m_D3D9Param;
	uint32 m_nVertexProcessType;
};