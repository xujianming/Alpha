#include "stdafx.h"

#include "CRenderer.h"
#include "CGraphicD3D9.h"
#pragma comment(lib, "d3dx9.lib")
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

void CRenderer::SetMainScene( CScene *pScene )
{
	m_pMainScene = pScene;
}
