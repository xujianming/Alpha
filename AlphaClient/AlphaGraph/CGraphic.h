#pragma once
#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
#include "CGraphicResMgr.h"
#include "CRenderCommandMgr.h"
#include "CVertexFormatMgr.h"

class CAlphaWindow;
class CGraphicResMgr;

class CGraphic: public IAlphaUnknown
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

	uint32 GetCurFrame();

	CRenderCommandMgr& GetRenderCommandMgr();

	CVertexFormatMgr& GetVertexFormatMgr();

	CGraphicResMgr& GetResMgr();

	void AddRef();

	void Release();

	void GetRef();

protected:	
	virtual bool CreateSuitableDevice();

	CRenderCommandMgr m_RenderCommandMgr;
	CVertexFormatMgr m_VertexFormatMgr;
	CGraphicResMgr m_ResMgr;

	CAlphaWindow* m_pWnd;
	float m_fHWVertexShaderVersion;
	float m_fHWPixelShaderVersion;
	uint8 m_nMaxSupportRenderTargetCnt;
	uint32 m_nCurFrame;
};