#include "stdafx.h"
#include "CRenderCommandMgr.h"
#include "CGraphic.h"

CRenderCommandMgr::CRenderCommandMgr(CGraphic* pGraphic):
	m_pGraphic(pGraphic)
{
}

CRenderCommandMgr::~CRenderCommandMgr()
{
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
	m_sPrimiveInfo.nPrimitiveGroupCnt ++;
	m_sPrimiveInfo.nVertexCnt += vertexCnt;
	m_sPrimiveInfo.nPrimitiveCnt += primitiveCnt;
	m_pGraphic->GetRenderStateMgr().Apply(material, primitiveType, vertexCnt, primitiveCnt, vertexType, vertexStride, arrVertex, arrIndex);
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf )
{
	m_sPrimiveInfo.nPrimitiveGroupCnt ++;
	m_sPrimiveInfo.nVertexCnt += vertexCnt;
	m_sPrimiveInfo.nPrimitiveCnt += primitiveCnt;
	m_pGraphic->GetRenderStateMgr().Apply(material, primitiveType, vertexCnt, primitiveCnt, vertexType, vertexBuf, indexBuf);
}

void CRenderCommandMgr::pushEnvir( SRenderEnvir envirState )
{
	m_envirStack.push_back(envirState);
}

void CRenderCommandMgr::popEnvir()
{
	m_envirStack.pop_back();
}

bool CRenderCommandMgr::isEmpty()
{
	return m_envirStack.size() == 0;
}
