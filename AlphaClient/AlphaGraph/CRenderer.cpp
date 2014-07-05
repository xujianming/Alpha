#include "stdafx.h"

#include "CRenderer.h"
#include "CGraphicD3D9.h"

CRenderer::CRenderer()
{

}

CRenderer::~CRenderer()
{

}

void CRenderer::Initialize( CAlphaWindow* pWnd )
{
	m_pWnd = pWnd;
	m_pGraphic = new CGraphicD3D9(m_pWnd);
	m_pGraphic->Create();
}

void CRenderer::EnterOneFrame()
{
	if (!m_pGraphic->RenderBegin())
		return;

	m_pGraphic->RenderEnd();
}
