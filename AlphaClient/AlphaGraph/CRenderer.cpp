#include "stdafx.h"

#include "CRenderer.h"
#include "CGraphicD3D9.h"
#include "CModel.h"
#include "AlphaCommon\CAlphaWindow.h"
#pragma comment(lib, "d3dx9.lib")
CRenderer::CRenderer()
{
	m_pModel = 0;
}

CRenderer::~CRenderer()
{

}

void CRenderer::Initialize( CAlphaWindow* pWnd )
{
	m_pWnd = pWnd;
	m_pGraphic = new CGraphicD3D9(m_pWnd);
	m_pGraphic->Create();
	
	m_pModel = new CModel;
	bool result = m_pModel->Initialize(m_pGraphic->GetDevice(), "../data/cube.txt", "../data/seafloor.dds");
	if(!result)
	{
		MessageBox(m_pWnd->GetHandle(), "Could not initialize the model object.", "Error", MB_OK);
		return;
	}
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
