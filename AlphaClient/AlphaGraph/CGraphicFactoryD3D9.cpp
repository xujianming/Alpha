#include "stdafx.h"
#include "CGraphicFactoryD3D9.h"
#include "CVertexFormatD3D9.h"
#include "CTextureD3D9.h"
#include "CGeometryBufferD3D9.h"

CGraphicFactoryD3D9::CGraphicFactoryD3D9( CGraphic* pGraphic ):
	CGraphicFactory(pGraphic)
{
	
}

CGraphicFactoryD3D9::~CGraphicFactoryD3D9()
{

}

CVertexFormat* CGraphicFactoryD3D9::CreateVertexFormat()
{
	return new CVertexFormatD3D9(m_pGraphic);
}

CTexture* CGraphicFactoryD3D9::CreateTexture()
{
	return new CTextureD3D9(m_pGraphic);
}

CGeometryBuffer* CGraphicFactoryD3D9::CreateVertexBuffer()
{

}

CGeometryBuffer* CGraphicFactoryD3D9::CreateIndexBuffer()
{

}

