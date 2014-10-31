#include "stdafx.h"
#include "CGraphic.h"
#include "AlphaCommon/CAlphaWindow.h"
#include "CRenderCommandMgr.h"
#include "CGraphicFactory.h"
#include "CTexture.h"
#include "CShader.h"
#include "CVertexFormat.h"

CGraphic::CGraphic( CAlphaWindow* pWnd ):
	m_pWnd(pWnd),
	m_cRenderCommandMgr(this),
	m_cVertexFormatMgr(this),
	m_ResMgr(this),
	m_fHWPixelShaderVersion(0),
	m_fHWVertexShaderVersion(0),
	m_nMaxSupportRenderTargetCnt(1),
	m_pGraphicFactory(nullptr),
	m_nRef(1)
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
	m_nCurFrame ++;
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
	m_ResMgr.Clear();
}

void CGraphic::DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
	m_cRenderCommandMgr.DrawPrimitive(material, primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexStride, arrVertex, arrIndex );
}

void CGraphic::DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuffer, CGeometryBuffer* indexBuffer )
{
	m_cRenderCommandMgr.DrawPrimitive(material, primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexBuffer, indexBuffer );
}

uint32 CGraphic::GetCurFrame()
{
	return m_nCurFrame;
}

void CGraphic::AddRef()
{
	m_nRef ++;
}

void CGraphic::Release()
{
	if (m_nRef --)
	{
		Destroy();
		delete this;
	}
}

uint32 CGraphic::GetRef()
{
	return m_nRef;
}

CTexture* CGraphic::CreateTextureFromFile( char* szFileName )
{
	CTexture* pTexture = m_pGraphicFactory->CreateTexture();
	pTexture->CreateTextureFromFile(szFileName);
	return  pTexture;
}

CRenderCommandMgr& CGraphic::GetRenderCommandMgr()
{
	return m_cRenderCommandMgr;
}

CVertexFormatMgr& CGraphic::GetVertexFormatMgr()
{
	return m_cVertexFormatMgr;
}

CGraphicResMgr& CGraphic::GetResMgr()
{
	return m_ResMgr;
}


CGraphicFactory& CGraphic::GetCraphicFactor()
{
	return *m_pGraphicFactory;
}

CRenderStateMgr& CGraphic::GetRenderStateMgr()
{
	return *m_pRenderStateMgr;
}


CShader* CGraphic::CreateShaderFromFile( const char* szFileName )
{
	CShader* pShader = m_pGraphicFactory->CreateShader();
	pShader->CreateShaderFromFile(szFileName);
	return pShader;
}

uint16 CGraphic::CreateVertexFormat( SVertexElem* arrElem, uint16 cnt )
{
	uint16 nFormat = GetVertexFormatMgr().GetVertexFormat(arrElem, cnt);
	if (nFormat != INVALID_16BIT)
		return nFormat;
	CVertexFormat* pFormat = GetCraphicFactor().CreateVertexFormat();
	if (!pFormat->CreateVertexFormat(arrElem, cnt))
	{
		SAFE_DELETE(pFormat);
		return INVALID_16BIT;
	}
	nFormat = GetVertexFormatMgr().AddVertexFormat(pFormat);
	return nFormat;
}
