#pragma once

#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
#include "CRenderCommandMgr.h"
#include <vector>

using namespace std;

class CShader;
class CGraphic;
class CGeometryBuffer;

class CRenderStateMgr
{
public:
	CRenderStateMgr(CGraphic* pGraphic);
	
	virtual ~CRenderStateMgr();

	void Apply( const SMaterial& sMaterial, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex);

	void Apply( const SMaterial& sMaterial, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf);

protected:

	virtual void SetShader(CShader* pShader);

	virtual void SetRenderTargetParam(const SRenderTargetInfo& info) = 0;

	virtual void SetStencilParam() = 0;

	virtual void SetScissorRect() = 0;

	void ApplyRenderTargetParam();

	virtual void SetAlphaBlend(uint8 nSrcBlend, uint8 nDesBlend) = 0;

	virtual void SetZTest(uint8 nZTestFun, bool bZWR) = 0;

	virtual void SetFillModel(uint8 nRGBWriteFlag, uint8 nCullType) = 0;

	void ApplyMaterialParam(const SMaterial& material);

	void Reset();

	virtual void Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint16 nVertexFormat, uint16 nVertexStride, const void* pArrVertex, const void* pArrIndex) = 0;

	virtual void Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint16 nVertexFormat, CGeometryBuffer* pVertexBuf, CGeometryBuffer* pIndexBuf) = 0; 

	CGraphic* m_pGraphic;

	vector< CVector4f > m_vecVertexShaderParam;

	vector< CVector4f > m_vecPixelShaderParam;

	uint32 m_nVertexRegisterCnt;
	
	uint32 m_nPixelRegisterCnt;
};