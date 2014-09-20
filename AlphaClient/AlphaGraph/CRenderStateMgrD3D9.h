#pragma once

#include "CRenderStateMgr.h"

class CGraphic;

class CRenderStateMgrD3D9: CRenderStateMgr
{
public:
	CRenderStateMgrD3D9(CGraphic* pGraphic);

	~CRenderStateMgrD3D9();

protected:
	virtual void SetAlphaBlend(uint8 nSrcBlend, uint8 nDesBlend);

	virtual void SetZTest(uint8 nZTestFun, bool bZWR);

	virtual void SetFillModel(uint8 nRGBWriteFlag, uint8 nCullType);

	virtual void SetRenderTargetParam();

	virtual void SetStencilParam();

	virtual void SetScissorRect();

	virtual void SetShader(CShader* pShader);

	virtual void Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint8 nVertexFormat, uint16 nVertexStride, const void* pArrVertex, const void* pArrIndex);

	virtual void Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint8 nVertexFormat, CGeometryBuffer* pVertexBuf, CGeometryBuffer* pIndexBuf);

};