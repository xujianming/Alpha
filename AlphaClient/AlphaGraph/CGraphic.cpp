#include "stdafx.h"
#include "CGraphic.h"
#include "AlphaCommon/CAlphaWindow.h"

CGraphic::CGraphic( CAlphaWindow* pWnd ):
	m_pWnd(pWnd),
	m_pRenderCommandMgr(nullptr)
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
