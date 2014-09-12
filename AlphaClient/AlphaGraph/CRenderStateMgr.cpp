#include "stdafx.h"
#include "CRenderStateMgr.h"

CRenderStateMgr::CRenderStateMgr( CGraphic* pGraphic ):
	m_pGraphic(pGraphic)
{

}

CRenderStateMgr::~CRenderStateMgr()
{

}

void CRenderStateMgr::Apply( const SMaterial& sMaterial, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
	ApplyRenderTargetParam();
	ApplyMaterialParam(sMaterial);
	SetShader(sMaterial.m_pShader);
	Draw(primitiveType, vertexCnt, primitiveCnt, vertexType, vertexStride, arrVertex, arrIndex);
}

void CRenderStateMgr::Apply( const SMaterial& sMaterial, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf )
{
	ApplyRenderTargetParam();
	ApplyMaterialParam(sMaterial);
	SetShader(sMaterial.m_pShader);
	Draw(primitiveType, vertexCnt, primitiveCnt, vertexType, vertexBuf, indexBuf);

}

void CRenderStateMgr::SetShader( CShader* pShader )
{

}

void CRenderStateMgr::ApplyRenderTargetParam()
{

}

void CRenderStateMgr::ApplyMaterialParam( const SMaterial& material )
{
	SetAlphaBlend(material.m_nSrcBlend, material.m_nSrcBlend);

	SetZTest(material.m_nZTestFun, material.m_bZWR);

	SetFillModel(material.m_nRGBWriteFlag, material.m_nCullType);
}
