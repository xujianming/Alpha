#include "stdafx.h"
#include "CGraphic.h"
#include "CRenderCommandMgr.h"
#include "CRenderStateMgr.h"

CRenderCommandMgr::CRenderCommandMgr(CGraphic* pGraphic):
	m_pGraphic(pGraphic)
{
	m_envirStack.clear();
	m_curEnvir.ambient;
	m_curEnvir.nLighCnt = 0;
}

CRenderCommandMgr::~CRenderCommandMgr()
{
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
//	m_sPrimiveInfo.nPrimitiveGroupCnt ++;
//	m_sPrimiveInfo.nVertexCnt += vertexCnt;
//	m_sPrimiveInfo.nPrimitiveCnt += primitiveCnt;
	BuildViewSpaceLigth();
	m_pGraphic->GetRenderStateMgr().Apply(material, matWorld, nMatCnt, primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexStride, arrVertex, arrIndex);
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf )
{
//	m_sPrimiveInfo.nPrimitiveGroupCnt ++;
//	m_sPrimiveInfo.nVertexCnt += vertexCnt;
//	m_sPrimiveInfo.nPrimitiveCnt += primitiveCnt;
	BuildViewSpaceLigth();
	m_pGraphic->GetRenderStateMgr().Apply(material, matWorld, nMatCnt, primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexBuf, indexBuf);
}

void CRenderCommandMgr::PushEnvir( SRenderEnvir envirState )
{
	m_envirStack.push_back(envirState);
	SRenderTargetInfo& info = m_curEnvir.renderTargetInfo;
	for (uint8 i = 0; i < MAX_RENDER_TARGET; i ++)
	{
		if (info.pRenderTargets[i])
			info.pRenderTargets[i]->AddRef();
	}
	if (info.pDepthpRenderTarget)
		info.pDepthpRenderTarget->AddRef();
	m_curEnvir = *m_envirStack.rbegin();
}

void CRenderCommandMgr::PopEnvir()
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
	//m_curEnvir.matViewInvert = matView;
	//m_curEnvir.matViewInvert.invert();
	m_curEnvir.matViewProject = m_curEnvir.matView * m_curEnvir.matProject;
	m_curEnvir.bLightInvalid = true;
}

const CMatrix& CRenderCommandMgr::GetView()
{
	return m_curEnvir.matView;
}

void CRenderCommandMgr::SetProj( const CMatrix& matProj )
{
	m_curEnvir.matProject = matProj;
	//m_curEnvir.matProjectInvert = matProj;
	//m_curEnvir.matProjectInvert.invert();
	m_curEnvir.matViewProject = m_curEnvir.matView * m_curEnvir.matProject;
}

const CMatrix& CRenderCommandMgr::GetProj()
{
	return m_curEnvir.matProject;
}

void CRenderCommandMgr::SetLigth( const SLight* arrLigth, uint8 nCnt )
{
	memcpy(m_curEnvir.arryLight, arrLigth, min(m_curEnvir.MAX_LIGHT, nCnt));
	m_curEnvir.bLightInvalid = true;
}

void CRenderCommandMgr::AddLight( const SLight& light )
{
	if (m_curEnvir.nLighCnt + 1 >= m_curEnvir.MAX_LIGHT)
		return;
	m_curEnvir.arryLight[m_curEnvir.nLighCnt ++] = light;
	m_curEnvir.bLightInvalid = true;
}

void CRenderCommandMgr::BuildViewSpaceLigth()
{
	if (!m_curEnvir.bLightInvalid)
		return;
	m_curEnvir.bLightInvalid = false;
	for (uint8 i = 0; i < m_curEnvir.nLighCnt; i ++)
	{
		m_curEnvir.arrLightPos[i] = CVector4f(m_curEnvir.arryLight[i].m_vPos, 1.0f);// * m_curEnvir.matView;
		m_curEnvir.arrLightDir[i] = CVector4f(m_curEnvir.arryLight[i].m_vDir, 1.0f);// * m_curEnvir.matView;
		m_curEnvir.arrLightDir[i].v[3] = cos(m_curEnvir.arryLight[i].m_fAngle / 2);
		for (uint8 j = 0; j < 4; j ++)
			m_curEnvir.arrLightColor[i].v[j] = ((m_curEnvir.arryLight[i].m_nColor >> j) & 0xff) / 255.0f;
		m_curEnvir.arrLightParam[i].v[0] = m_curEnvir.arryLight[i].m_fAtten0;
		m_curEnvir.arrLightParam[i].v[1] = m_curEnvir.arryLight[i].m_fAtten1;
		m_curEnvir.arrLightParam[i].v[2] = m_curEnvir.arryLight[i].m_fAtten2;
		m_curEnvir.arrLightParam[i].v[3] = m_curEnvir.arryLight[i].m_fRange;
	}
	memset(m_curEnvir.arrLightPos +  m_curEnvir.nLighCnt, 0x00, sizeof(CVector4f) * (m_curEnvir.MAX_LIGHT - m_curEnvir.nLighCnt));
	memset(m_curEnvir.arrLightDir +  m_curEnvir.nLighCnt, 0x00, sizeof(CVector4f) * (m_curEnvir.MAX_LIGHT - m_curEnvir.nLighCnt));
	memset(m_curEnvir.arrLightColor +  m_curEnvir.nLighCnt, 0x00, sizeof(CVector4f) * (m_curEnvir.MAX_LIGHT - m_curEnvir.nLighCnt));
	memset(m_curEnvir.arrLightParam +  m_curEnvir.nLighCnt, 0x00, sizeof(CVector4f) * (m_curEnvir.MAX_LIGHT - m_curEnvir.nLighCnt));
}

void CRenderCommandMgr::SetAmbient( const CVector4f& ambient )
{
	m_curEnvir.ambient = ambient;
}
