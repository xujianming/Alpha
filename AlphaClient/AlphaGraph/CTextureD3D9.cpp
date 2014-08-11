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
	m_nMipmaps = min(nMipMap, log(max(m_nWidth, m_nHeight)));
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
	return D3DXCreateTextureFromFile(pGraphicD3D9->GetDevice(), szFileName, (IDirect3DTexture9**)&m_pTexture) == D3D_OK;
}

IDirect3DBaseTexture9* CTextureD3D9::GetD3DTexture()
{
	return m_pSysTexture ? m_pSysTexture : m_pTexture;
}
