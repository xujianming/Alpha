////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
#include "stdafx.h"
#include "CTexture.h"

CTexture::CTexture( CGraphic* pGraphic, EResourceType eResType ):
	CGraphicRes(pGraphic, eResType),
	m_nWidth(0),
	m_nHeight(0),
	m_nDepth(0),
	m_eFormat(eTF_ARGB32),
	m_nMipmaps(1)
{

}


CTexture::~CTexture()
{
}
