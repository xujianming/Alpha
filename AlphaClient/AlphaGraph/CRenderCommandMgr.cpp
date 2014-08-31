#include "stdafx.h"
#include "CRenderCommandMgr.h"


CRenderCommandMgr::CRenderCommandMgr(CGraphic* pGraphic):
	m_pGraphic(pGraphic)
{
}

CRenderCommandMgr::~CRenderCommandMgr()
{
}

void CRenderCommandMgr::DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
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
