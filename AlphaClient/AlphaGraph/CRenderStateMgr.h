#pragma once

#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"

class CShader;;
class CGraphic;
class CGeometryBuffer;

class CRenderStateMgr
{
public:
	CRenderStateMgr(CGraphic* pGraphic);
	
	virtual ~CRenderStateMgr();

	void Apply( const SMaterial& sMaterial, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, uint32 nVertexFormat, const void* arrVertex, const void* arrIndex);

	void Apply( const SMaterial& sMaterial, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint32 nVertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf);

protected:

	virtual void SetShader(CShader* pShader) = 0;

	virtual void SetRenderTargetParam() = 0;

	virtual void SetStencilParam() = 0;

	virtual void SetScissorRect() = 0;

	void ApplyRenderTargetParam();


	virtual void SetAlphaBlend(uint8 nSrcBlend, uint8 nDesBlend) = 0;

	virtual void SetZTest(uint8 nZTestFun, bool bZWR) = 0;

	virtual void SetFillModel(uint8 nRGBWriteFlag, uint8 nCullType) = 0;

	void ApplyMaterialParam(const SMaterial& material);

	void Reset();

	virtual void Draw(EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType,  uint32 nVertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex) = 0;

	virtual void Draw(EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType,  uint32 nVertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf) = 0;

	CGraphic* m_pGraphic;
};