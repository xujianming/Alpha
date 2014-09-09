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

	void SetShader(CShader* pProgram);

	void SetAlphaBlend();

	void SetZTest(bool bTest);

	void SetFillModel();

	void SetRenderTargetParam();

	void SetStencilParam();

	void SetScissorRect();

	void ApplyMaterialParam();

	void ApplyRenderTargetParam();

	void Reset();

	void Apply( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex);
	
	void Apply( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf);


protected:
	CGraphic* m_pGraphic;
};