#include "stdafx.h"
#include "CGraphic.h"
#include "AlphaCommon/CAlphaWindow.h"
#include "CRenderCommandMgr.h"

CGraphic::CGraphic( CAlphaWindow* pWnd ):
	m_pWnd(pWnd),
	m_pRenderCommandMgr(nullptr),
	m_fHWPixelShaderVersion(0),
	m_fHWVertexShaderVersion(0),
	m_nMaxSupportRenderTargetCnt(1)
{

}

CGraphic::~CGraphic()
{

}

bool CGraphic::Create()
{
	if (!CreateSuitableDevice())
		return false;
	if (m_fHWVertexShaderVersion < 2.0 || m_fHWPixelShaderVersion < 2.0)
		return false;

	return true;
}

bool CGraphic::CreateSuitableDevice()
{
	return true;
}

bool CGraphic::RenderBegin()
{
	SetRenderTarget();
	return m_pWnd && m_pWnd->IsShow();
}

void CGraphic::RenderEnd()
{

}

bool CGraphic::CreateBackBuffer()
{
	return true;
}

bool CGraphic::SetRenderTarget()
{
	return true;
}

void CGraphic::Destroy()
{

}

void CGraphic::DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
	m_pRenderCommandMgr->DrawPrimitive(material, primitiveType, vertexCnt, primitiveCnt, vertexType, vertexStride, arrVertex, arrIndex );
}