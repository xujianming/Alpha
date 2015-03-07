#pragma once

#include <d3d9.h>
#include "CTexture.h"
#include <d3dx9.h>

#define MAX_MIPMAP 4

class CTextureD3D9: public CTexture
{
public:
	CTextureD3D9(CGraphic* pGraphic, EResourceType eResType = ERT_Texture);
	~CTextureD3D9();

	virtual bool CreateTexture(uint32 nWidth, uint32 nHeight, uint32 nDepth, ETextureFormat eFormat, int32 nMipMap, bool bPoolManager);

	bool CreateTextureFromFile(char* szFileName);

	IDirect3DBaseTexture9* GetD3DTexture();

protected:

	IDirect3DBaseTexture9* CreateTexture( bool bSys, bool bFetchSize);

	IDirect3DBaseTexture9* m_pSysTexture;
	IDirect3DBaseTexture9* m_pTexture;
};

class CRenderTargetD3D: public CTextureD3D9
{
public:
	CRenderTargetD3D(CGraphic* pGraphic);
	~CRenderTargetD3D();

	virtual bool CreateRenderTarget(uint32 nWidth, uint32 nHeight, ETextureFormat eTargetFormat, int32 nMipMap, ETextureFormat eDepthSttencilFormat);
	IDirect3DSurface9* GetRenderTargetSuface() { return m_pRenderTarget; }
	IDirect3DSurface9* GetDepthStencilSuface() { return m_pDepthStencil; }
	ETextureFormat GetDepthStencilFormat() { return m_eDepthStencilFmt; }
protected:
	IDirect3DSurface9* m_pRenderTarget;
	IDirect3DSurface9* m_pDepthStencil;
	ETextureFormat m_eDepthStencilFmt;
};