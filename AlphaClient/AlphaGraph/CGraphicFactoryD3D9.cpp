#include "stdafx.h"
#include "CGraphicFactoryD3D9.h"
#include "CVertexFormatD3D9.h"
#include "CTextureD3D9.h"
#include "CGeometryBufferD3D9.h"
#include "CShaderD3D9.h"

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

CTexture* CGraphicFactoryD3D9::CreateRenderTarget()
{
	return new CRenderTargetD3D(m_pGraphic);
}

CGeometryBuffer* CGraphicFactoryD3D9::CreateVertexBuffer()
{
	return new CVertexBufferD3D9(m_pGraphic);
}

CGeometryBuffer* CGraphicFactoryD3D9::CreateIndexBuffer()
{
	return new CIndexBufferD3D9(m_pGraphic);
}

CShader* CGraphicFactoryD3D9::CreateShader()
{
	return new CShaderD3D9(m_pGraphic);
}
