#include "stdafx.h"
#include "CRenderStateMgrD3D9.h"
#include "CGraphicD3D9.h"
#include "CGeometryBufferD3D9.h"


CRenderStateMgrD3D9::CRenderStateMgrD3D9(CGraphic* pGraphic):
	CRenderStateMgr(pGraphic)
{

}

CRenderStateMgrD3D9::~CRenderStateMgrD3D9()
{

}

void CRenderStateMgrD3D9::SetAlphaBlend( uint8 nSrcBlend, uint8 nDesBlend )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	pGraphic->GetDevice()->SetRenderState(D3DRS_SRCBLEND, nSrcBlend);
	pGraphic->GetDevice()->SetRenderState(D3DRS_DESTBLEND, nDesBlend);
}

void CRenderStateMgrD3D9::SetZTest( uint8 nZTestFun, bool bZWR )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	pGraphic->GetDevice()->SetRenderState(D3DRS_ZFUNC, nZTestFun);
	pGraphic->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, bZWR);
}

void CRenderStateMgrD3D9::SetFillModel( uint8 nRGBWriteFlag, uint8 nCullType )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	//pGraphic->GetDevice()->SetRenderState(d3drs, nCullType);
	pGraphic->GetDevice()->SetRenderState(D3DRS_FILLMODE, nCullType);
}

void CRenderStateMgrD3D9::SetRenderTargetParam()
{

}

void CRenderStateMgrD3D9::SetStencilParam()
{

}

void CRenderStateMgrD3D9::SetScissorRect()
{

}

void CRenderStateMgrD3D9::SetShader( CShader* pShader )
{

}

void CRenderStateMgrD3D9::Draw( EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{

}

void CRenderStateMgrD3D9::Draw( EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf )
{
	CVertexBufferD3D9* pVertexBuffer = static_cast<CVertexBufferD3D9*>(vertexBuf);
	CIndexBufferD3D9* pIndexBuffer = static_cast<CIndexBufferD3D9*>(indexBuf);
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	pGraphic->GetDevice()->SetStreamSource(0, static_cast<IDirect3DVertexBuffer9*>(pVertexBuffer->GetD3DBuffer()), 0, pVertexBuffer->GetStride());
	pGraphic->GetDevice()->SetIndices(static_cast<IDirect3DIndexBuffer9*>(pIndexBuffer->GetD3DBuffer()))
	pGraphic->GetDevice()->DrawIndexedPrimitive(primitiveType, 0, vertexCnt, 0, primitiveCnt)
}

