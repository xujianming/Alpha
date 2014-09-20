#include "stdafx.h"
#include "CRenderStateMgrD3D9.h"
#include "CGraphicD3D9.h"
#include "CGeometryBufferD3D9.h"
#include "CVertexFormatD3D9.h"

D3DPRIMITIVETYPE g_PrimitiyType[ePT_Cnt] = 
{
	D3DPT_POINTLIST,
	D3DPT_LINELIST,
	D3DPT_LINESTRIP,
	D3DPT_TRIANGLELIST,
	D3DPT_TRIANGLESTRIP,
	D3DPT_TRIANGLEFAN,
};

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
	if (nZTestFun == eMCF_Disable)
		pGraphic->GetDevice()->SetRenderState(D3DRS_ZENABLE, false);
	else
	{
		pGraphic->GetDevice()->SetRenderState(D3DRS_ZENABLE, true);
		pGraphic->GetDevice()->SetRenderState(D3DRS_ZFUNC, nZTestFun);
	}
	pGraphic->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, bZWR);
}

void CRenderStateMgrD3D9::SetFillModel( uint8 nRGBWriteFlag, uint8 nCullType )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	pGraphic->GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, nRGBWriteFlag);
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

void CRenderStateMgrD3D9::Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint8 nVertexFormat, uint16 nVertexStride, const void* pArrVertex, const void* pArrIndex)
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	CVertexFormatD3D9* pVertexVormat = static_cast<CVertexFormatD3D9*>(pGraphic->GetVertexFormatMgr().GetVertexFormat(nVertexFormat));
	pGraphic->GetDevice()->SetVertexDeclaration(pVertexVormat->GetVertexDeclaration());
	if (pArrIndex)
		pGraphic->GetDevice()->DrawIndexedPrimitiveUP(g_PrimitiyType[ePrimitiveType], 0, nVertexCnt, nPrimitiveCnt, pArrIndex, D3DFMT_INDEX16, pArrVertex, nVertexStride);
	else
		pGraphic->GetDevice()->DrawPrimitiveUP(g_PrimitiyType[ePrimitiveType], nPrimitiveCnt, pArrVertex, nVertexStride);
}

void CRenderStateMgrD3D9::Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint8 nVertexFormat, CGeometryBuffer* pVertexBuf, CGeometryBuffer* pIndexBuf)
{
	CVertexBufferD3D9* pVertexBuffer = static_cast<CVertexBufferD3D9*>(pVertexBuf);
	CIndexBufferD3D9* pIndexBuffer = static_cast<CIndexBufferD3D9*>(pIndexBuf);
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	CVertexFormatD3D9* pVertexVormat = static_cast<CVertexFormatD3D9*>(pGraphic->GetVertexFormatMgr().GetVertexFormat(nVertexFormat));
	pGraphic->GetDevice()->SetVertexDeclaration(pVertexVormat->GetVertexDeclaration());
	pGraphic->GetDevice()->SetStreamSource(0, static_cast<IDirect3DVertexBuffer9*>(pVertexBuffer->GetD3DBuffer()), 0, pVertexBuffer->GetStride());
	if (pIndexBuffer)
	{
		pGraphic->GetDevice()->SetIndices(static_cast<IDirect3DIndexBuffer9*>(pIndexBuffer->GetD3DBuffer()));
		pGraphic->GetDevice()->DrawIndexedPrimitive(g_PrimitiyType[ePrimitiveType], 0, nVertexCnt, 0, nPrimitiveCnt);
	}
	else
	{
		pGraphic->GetDevice()->DrawPrimitive(g_PrimitiyType[ePrimitiveType], 0, nPrimitiveCnt);
	}
}