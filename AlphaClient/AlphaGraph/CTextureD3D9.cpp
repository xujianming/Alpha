#include "stdafx.h"
#include "CTextureD3D9.h"
#include "CGraphicD3D9.h"
#include <math.h>
#include <d3dx9.h>
CTextureD3D9::CTextureD3D9( CGraphic* pGraphic, EResourceType eResType /*= ERT_Texture*/ ):
	CTexture(pGraphic, eResType),
	m_pSysTexture(nullptr),
	m_pTexture(nullptr)
{

}

CTextureD3D9::~CTextureD3D9()
{
	SAFE_RELEASE(m_pSysTexture);
	SAFE_RELEASE(m_pTexture);
}


bool CTextureD3D9::CreateTexture( uint32 nWidth, uint32 nHeight, uint32 nDepth, ETextureFormat eFormat, int32 nMipMap, bool bPoolManager )
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nDepth = nDepth;
	m_eFormat = eFormat;
	m_nMipmaps = min(MAX_MIPMAP, uint32(nMipMap));
	m_nMipmaps = min(m_nMipmaps, (uint32)log(max(m_nWidth, m_nHeight)));
	if (bPoolManager)
		m_pSysTexture = CreateTexture(true, true);
	else
		m_pTexture = CreateTexture(false, true);
	if (!m_pTexture)
		SetVedioMemSize(0);
	else
	{
		if (IsCubeTexture())
			SetVedioMemSize( 6 * m_nWidth * m_nWidth * GetBitPerPixel(eFormat) / 8);
		else
			SetVedioMemSize( m_nWidth * max(1, m_nHeight) * max(1, m_nDepth) * GetBitPerPixel(eFormat) / 8);
	}
	Use();
	return m_pSysTexture || m_pTexture;
}

IDirect3DBaseTexture9* CTextureD3D9::CreateTexture( bool bSys, bool bFetchSize )
{
	D3DPOOL pool = bSys ? D3DPOOL_SYSTEMMEM : D3DPOOL_DEFAULT;
	CGraphicD3D9* pGraphicD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	uint32 usage = IsDepthFormat(GetFormat()) ? D3DUSAGE_DEPTHSTENCIL : 0;
	D3DFORMAT format = pGraphicD3D9->ToTextureFmt(GetFormat());
	
	if (IsCubeTexture())
	{
		IDirect3DCubeTexture9* pNewTexture = nullptr;
		if (pGraphicD3D9->GetDevice()->CreateCubeTexture(GetWidth(), GetMipmaps(), usage, format, pool, &pNewTexture, nullptr )
			!= D3D_OK)
		{
			SAFE_RELEASE(pNewTexture);
			return nullptr;
		}
		if (bFetchSize)
		{
			D3DSURFACE_DESC desc;
			pNewTexture->GetLevelDesc(0, &desc);
			m_nWidth = desc.Width;
			m_nHeight = 0;
			m_nDepth = 0;
		}
		return pNewTexture;
	}
	else if (IsVolumeTexture())
	{
		IDirect3DVolumeTexture9* pNewTexture = nullptr;
		if (pGraphicD3D9->GetDevice()->CreateVolumeTexture(GetWidth(), GetHeight(), GetDepth(), GetMipmaps(), usage, format, pool, &pNewTexture, nullptr )
			!= D3D_OK)
		{
			SAFE_RELEASE(pNewTexture);
			return nullptr;
		}
		if (bFetchSize)
		{
			D3DVOLUME_DESC desc;
			pNewTexture->GetLevelDesc(0, &desc);
			m_nWidth = desc.Width;
			m_nHeight = desc.Height;
			m_nDepth = desc.Depth;
		}
		return pNewTexture;
	}
	else
	{
		IDirect3DTexture9* pNewTexture = nullptr;
		if (pGraphicD3D9->GetDevice()->CreateTexture(GetWidth(), GetHeight(), GetMipmaps(), usage, format, pool, &pNewTexture, nullptr )
			!= D3D_OK)
		{
			SAFE_RELEASE(pNewTexture);
			return nullptr;
		}
		if (bFetchSize)
		{
			D3DSURFACE_DESC desc;
			pNewTexture->GetLevelDesc(0, &desc);
			m_nWidth = desc.Width;
			m_nHeight = desc.Height;
			m_nDepth = 0;
		}
		return pNewTexture;
	}
}

bool CTextureD3D9::CreateTextureFromFile( char* szFileName )
{
	CGraphicD3D9* pGraphicD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	if (D3DXCreateTextureFromFile(pGraphicD3D9->GetDevice(), szFileName, (IDirect3DTexture9**)&m_pTexture) != D3D_OK)
		return false;
	D3DSURFACE_DESC desc;
	((IDirect3DTexture9*) m_pTexture)->GetLevelDesc(0, &desc);
	m_nWidth = desc.Width;
	m_nHeight = desc.Height;
	m_nDepth = 0;
	m_eFormat = pGraphicD3D9->FromD3DFmt(desc.Format);
	m_nMipmaps = ((IDirect3DTexture9*) m_pTexture)->GetLevelCount();
	uint32 nSize = m_pTexture ? m_nWidth * m_nHeight * GetBitPerPixel(m_eFormat) / 8 : 0;
	SetVedioMemSize(nSize);
	return true;
}

IDirect3DBaseTexture9* CTextureD3D9::GetD3DTexture()
{
	return m_pSysTexture ? m_pSysTexture : m_pTexture;
}


bool CTextureD3D9::FillFromMemory(void* pMemory, ETextureFormat eFormat, const CIRect* rect, uint32 nMipMapLevel)
{
	if (!Is2DTexture())
		return false;

	if (!m_pSysTexture && !m_pTexture)
		return false;

	uint32 nWidth = m_nWidth;
	uint32 nHeight = m_nHeight;
	for (uint32 i = 0; i < nMipMapLevel; i++)
	{
		nWidth >>= 1;
		nHeight >>= 1;
	}
	RECT rectDes = { 0, 0, nWidth, nHeight };
	if (rect)
	{
		rectDes.left = rect->left;
		rectDes.right = rect->right;
		rectDes.top = rect->top;
		rectDes.bottom = rect->bottom;
	}
		

	//非manager贴图不支持部分填充
	if (!m_pSysTexture && (rectDes.left != 0 || rectDes.top != 0 || rectDes.right != nWidth || rectDes.bottom != nHeight))
		return false;

	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	D3DFORMAT fmt = pGraphic->ToTextureFmt(eFormat);
	IDirect3DTexture9* pCurTexture;
	if (m_pSysTexture)
		pCurTexture = (IDirect3DTexture9*)m_pSysTexture;
	else
		pCurTexture = (IDirect3DTexture9*)m_pTexture;
	IDirect3DSurface9* pSurf;
	if (SUCCEEDED(pCurTexture->GetSurfaceLevel(nMipMapLevel, &pSurf)))
	{
		RECT rectSrc = { 0, 0, rectDes.right - rectDes.left, rectDes.bottom - rectDes.top };
		uint32 nPitch = GetPitch(eFormat, rectDes.bottom - rectDes.top);
		bool flag = SUCCEEDED(D3DXLoadSurfaceFromMemory(pSurf, nullptr, &rectDes, pMemory, fmt, nPitch, nullptr, &rectSrc, D3DX_FILTER_NONE, 0));
		SAFE_RELEASE(pSurf);
		return flag;
	}
	return false;
}


CRenderTargetD3D::CRenderTargetD3D( CGraphic* pGraphic ):
	CTextureD3D9(pGraphic, ERT_RenderTarget)
{

}

CRenderTargetD3D::~CRenderTargetD3D()
{

}

bool CRenderTargetD3D::CreateRenderTarget( uint32 nWidth, uint32 nHeight, ETextureFormat eTargetFormat, int32 nMipMap, ETextureFormat eDepthStencilFormat )
{
	CGraphicD3D9* pGraphicD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	D3DFORMAT targetFormat = pGraphicD3D9->ToTextureFmt(eTargetFormat);
	IDirect3DTexture9* pRenderTargetTex;
	if (pGraphicD3D9->GetDevice()->CreateTexture(nWidth, nHeight, 0, D3DUSAGE_RENDERTARGET, targetFormat, D3DPOOL_DEFAULT, &pRenderTargetTex, NULL) != D3D_OK)
		return false;
	m_pTexture = pRenderTargetTex;
	if (pRenderTargetTex->GetSurfaceLevel(0, &m_pRenderTarget))
		return false;
	
	D3DSURFACE_DESC desc;
	m_pRenderTarget->GetDesc(&desc);
	m_nWidth = desc.Width;
	m_nHeight = desc.Height;
	m_nDepth = 0;
	m_eFormat = pGraphicD3D9->FromD3DFmt(desc.Format);
	m_nMipmaps = pRenderTargetTex->GetLevelCount();
	m_eDepthStencilFmt = eDepthStencilFormat;
	D3DFORMAT depthStencilFmt = pGraphicD3D9->ToTextureFmt(m_eDepthStencilFmt);
	m_pDepthStencil = NULL;
	if (pGraphicD3D9->GetDevice()->CreateDepthStencilSurface(m_nWidth, m_nHeight, depthStencilFmt, 
		desc.MultiSampleType, desc.MultiSampleQuality, FALSE, &m_pDepthStencil, NULL) != S_OK)
	{
		SAFE_RELEASE(m_pRenderTarget);
		SAFE_RELEASE(m_pTexture);
		return false;
	}
	uint32 nSize = m_pTexture ? m_nWidth * m_nHeight * GetBitPerPixel(m_eFormat) / 8 : 0;
	nSize += m_pDepthStencil ? m_nWidth * m_nHeight * GetBitPerPixel(eDepthStencilFormat) / 8 : 0;
	SetVedioMemSize(nSize);
	return true;
}
