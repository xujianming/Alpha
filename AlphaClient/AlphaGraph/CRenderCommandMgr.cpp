#include "stdafx.h"
#include "CGraphic.h"
#include "CRenderCommandMgr.h"
#include "CRenderStateMgr.h"

CRenderCommandMgr::CRenderCommandMgr(CGraphic* pGraphic):
	m_pGraphic(pGraphic)
{
}

CRenderCommandMgr::~CRenderCommandMgr()
{
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
//	m_sPrimiveInfo.nPrimitiveGroupCnt ++;
//	m_sPrimiveInfo.nVertexCnt += vertexCnt;
//	m_sPrimiveInfo.nPrimitiveCnt += primitiveCnt;
	m_pGraphic->GetRenderStateMgr().Apply(material, matWorld, nMatCnt, primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexStride, arrVertex, arrIndex);
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf )
{
//	m_sPrimiveInfo.nPrimitiveGroupCnt ++;
//	m_sPrimiveInfo.nVertexCnt += vertexCnt;
//	m_sPrimiveInfo.nPrimitiveCnt += primitiveCnt;
	m_pGraphic->GetRenderStateMgr().Apply(material, matWorld, nMatCnt, primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexBuf, indexBuf);
}

void CRenderCommandMgr::pushEnvir( SRenderEnvir envirState )
{
	m_envirStack.push_back(envirState);
	SRenderTargetInfo& info = m_curEnvir.renderTargetInfo;
	for (uint8 i = 0; i < MAX_RENDER_TARGET; i ++)
	{
		if (info.pRenderTargets[i])
			info.pRenderTargets[i]->AddRef();
	}
	info.pDepthpRenderTarget->AddRef();
}

void CRenderCommandMgr::popEnvir()
{
	SRenderTargetInfo& info = m_curEnvir.renderTargetInfo;
	for (uint8 i = 0; i < MAX_RENDER_TARGET; i ++)
	{
		SAFE_RELEASE(info.pRenderTargets[i]);
	}
	SAFE_RELEASE(info.pDepthpRenderTarget);
	m_curEnvir = *m_envirStack.rbegin();
	m_envirStack.pop_back();
}

bool CRenderCommandMgr::isEmpty()
{
	return m_envirStack.size() == 0;
}

void CRenderCommandMgr::SetRenderTarget( CTexture* pRenderTargets[MAX_RENDER_TARGET], uint8 nCnt, CTexture* pDepthpRenderTargets )
{
	SRenderTargetInfo& info = m_curEnvir.renderTargetInfo;
	if (pDepthpRenderTargets)
		pDepthpRenderTargets->AddRef();
	SAFE_RELEASE(info.pDepthpRenderTarget);
	info.pDepthpRenderTarget = pDepthpRenderTargets;
	for (uint8 i = 0; i < nCnt; i ++)
	{
		if (pRenderTargets[i])
			pRenderTargets[i]->AddRef();
		SAFE_RELEASE(info.pRenderTargets[i]);
		info.pRenderTargets[i] = pRenderTargets[i];
	}
}

void CRenderCommandMgr::SetView( const CMatrix& matView )
{
	m_curEnvir.matView = matView;
	m_curEnvir.matViewInvert = matView;
	//m_curEnvir.matViewInvert.invert();
	m_curEnvir.matViewProject = m_curEnvir.matView * m_curEnvir.matProject;
}

const CMatrix& CRenderCommandMgr::GetView()
{
	return m_curEnvir.matView;
}

void CRenderCommandMgr::SetProj( const CMatrix& matProj )
{
	m_curEnvir.matProject = matProj;
	m_curEnvir.matProjectInvert = matProj;
	//m_curEnvir.matProjectInvert.invert();
	m_curEnvir.matViewProject = m_curEnvir.matView * m_curEnvir.matProject;
}

const CMatrix& CRenderCommandMgr::GetProj()
{
	return m_curEnvir.matProject;
}
