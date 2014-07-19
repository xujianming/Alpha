#pragma once
#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\CAlphaCommonType.h"

class CAlphaWindow;
class CRenderCommandMgr;
class CVertexFormatMgr;
class CGraphic
{
public:
	CGraphic(CAlphaWindow* pWnd);
	virtual ~CGraphic();

	virtual bool Create();

	virtual void Destroy();

	virtual bool RenderBegin();

	virtual void RenderEnd();

	virtual bool CreateBackBuffer();

	virtual bool SetRenderTarget();

	void DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex);

protected:	
	virtual bool CreateSuitableDevice();

	CRenderCommandMgr* m_pRenderCommandMgr;
	CVertexFormatMgr* m_pVertexFormatMgr;
	CAlphaWindow* m_pWnd;
	float m_fHWVertexShaderVersion;
	float m_fHWPixelShaderVersion;
	uint8 m_nMaxSupportRenderTargetCnt;
};