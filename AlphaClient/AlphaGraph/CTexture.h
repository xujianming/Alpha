#pragma once

#include "CGraphicRes.h"
#include "GraphicHelp.h"

class CTexture: public CGraphicRes
{
public:
	CTexture(CGraphic* pGraphic, EResourceType eResType = ERT_Texture);

	~CTexture();

	virtual bool CreateTexture(uint32 nWidht, uint32 nHeight, uint32 nDepth, ETextureFormat eFormat, int32 nMipMap, bool bPoolManager){ return false; }

	virtual bool CreateTextureFromFile(char* szFileName) { return false; };

//	bool CreateRenderTarget( uint32 nWidth, uint32 nHeight, uint32 nDepth, ETextureFormat eRecommandFormat, int32 nMipMap, bool bPoolManager) { return false; }

	uint32 GetWidth() 					{ return m_nWidth; }
	
	uint32 GetHeight()					{ return m_nHeight; }

	uint32 GetDepth()					{ return m_nDepth; }

	uint32 GetMipmaps()					{ return m_nMipmaps; }

	ETextureFormat GetFormat()			{ return m_eFormat; }

	bool Is2DTexture()					{ return !IsCubeTexture() && !IsVolumeTexture(); }

	bool IsCubeTexture()				{ return !GetHeight(); }

	bool IsVolumeTexture()				{ return GetHeight() && GetDepth();}

	virtual bool CreateRenderTarget( uint32 nWidth, uint32 nHeight, ETextureFormat eTargetFormat, 
		int32 nMipMap, ETextureFormat eDepthSttencilFormat ) { return false; }

protected:
	uint32 m_nWidth;
	uint32 m_nHeight;
	uint32 m_nDepth;
	uint32 m_nMipmaps;
	ETextureFormat m_eFormat;
};

