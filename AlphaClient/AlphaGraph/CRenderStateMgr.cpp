#include "stdafx.h"
#include "CRenderStateMgr.h"
#include "SMaterial.h"
#include "CGraphic.h"
#include "CShader.h"
#include "CTexture.h"

CRenderStateMgr::CRenderStateMgr( CGraphic* pGraphic ):
	m_pGraphic(pGraphic)
{

}

CRenderStateMgr::~CRenderStateMgr()
{

}

void CRenderStateMgr::Apply( const SMaterial& sMaterial, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex )
{
	ApplyRenderTargetParam();
	ApplyMaterialParam(sMaterial);
	if (sMaterial.m_pShader)
	{
		sMaterial.m_pShader->SetShaderParam(sMaterial, m_pGraphic->GetRenderCommandMgr().GetCurEnvir(), matWorld, nMatCnt);
		SetShader(sMaterial.m_pShader);
	}
	Draw(primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexStride, arrVertex, arrIndex);
}

void CRenderStateMgr::Apply( const SMaterial& sMaterial, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf )
{
	ApplyRenderTargetParam();
	ApplyMaterialParam(sMaterial);
	if (sMaterial.m_pShader)
	{
		sMaterial.m_pShader->SetShaderParam(sMaterial, m_pGraphic->GetRenderCommandMgr().GetCurEnvir(), matWorld, nMatCnt);
		SetShader(sMaterial.m_pShader);
	}
	Draw(primitiveType, vertexCnt, primitiveCnt, vertexFormat, vertexBuf, indexBuf);
}


void CRenderStateMgr::ApplyRenderTargetParam()
{
	SetRenderTargetParam(m_pGraphic->GetRenderCommandMgr().GetCurEnvir().renderTargetInfo);
}

void CRenderStateMgr::ApplyMaterialParam( const SMaterial& material )
{
	SetAlphaBlend(material.m_nSrcBlend, material.m_nSrcBlend);

	SetZTest(material.m_nZTestFun, material.m_bZWR);

	SetCullModel(material.m_nRGBWriteFlag, material.m_nCullType);
}

void CRenderStateMgr::SetShader( CShader* pShader )
{
	m_nVertexRegisterCnt = 0;
	m_nPixelRegisterCnt = 0;
	const vector<SShaderActiveParam*>& vecParam = pShader->GetVectorParams();
	for (uint32 i = 0; i < vecParam.size(); i ++)
	{
		if (vecParam[i]->m_nVertexRegisterCnt)
		{
			m_nVertexRegisterCnt = max(m_nVertexRegisterCnt, vecParam[i]->m_nVertexRegisterIndex + vecParam[i]->m_nVertexRegisterCnt);
			if (m_nVertexRegisterCnt > m_vecVertexShaderParam.size())
				m_vecVertexShaderParam.resize(m_nVertexRegisterCnt);
			memcpy(&m_vecVertexShaderParam[0] + vecParam[i]->m_nVertexRegisterIndex, &vecParam[i]->m_strBuffer[0],
				sizeof(CVector4f) * vecParam[i]->m_nVertexRegisterCnt);
		}
		if (vecParam[i]->m_nPixelRegisterCnt)
		{
			m_nPixelRegisterCnt = max(m_nPixelRegisterCnt, vecParam[i]->m_nPixelRegisterIndex + vecParam[i]->m_nPixelRegisterCnt);
			if (m_nPixelRegisterCnt > m_vecPixelShaderParam.size())
				m_vecPixelShaderParam.resize(m_nPixelRegisterCnt);
			memcpy(&m_vecPixelShaderParam[0] + vecParam[i]->m_nPixelRegisterIndex, &vecParam[i]->m_strBuffer[0],
				sizeof(CVector4f) * vecParam[i]->m_nPixelRegisterCnt);
		}
	}
}

void CRenderStateMgr::ClearBackBuffer(bool bClearTarget, bool bClearZBuffer, bool bClearStencil, uint32 nClearColor)
{
	ApplyRenderTargetParam();
	Clear(bClearTarget, bClearZBuffer, bClearStencil, nClearColor);
}