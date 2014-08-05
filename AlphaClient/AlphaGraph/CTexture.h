#pragma once

#include "CGraphicRes.h"

class CTexture: public CGraphicRes
{
public:
	CTexture();
	CTexture(const CTexture&);
	~CTexture();

	bool Initialize(IDirect3DDevice9* pDevice, char* wszFileName);
	void Shutdown();

	IDirect3DTexture9* GetTexture();

private:
	IDirect3DTexture9* m_texture;
	uint32 m_nWidth;
	uint32 m_nHeight;
	uint32 m_nDepth;
	uint32 m_nFormat;
};

