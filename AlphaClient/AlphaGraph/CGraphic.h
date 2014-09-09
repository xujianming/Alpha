#pragma once
#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
#include "CGraphicResMgr.h"
#include "CRenderCommandMgr.h"
#include "CVertexFormatMgr.h"
#include "AlphaCommon\IAlphaUnknown.h"
#include "CGeometryBuffer.h"

class CAlphaWindow;
class CGraphicResMgr;
class CGraphicFactory;
class CRenderStateMgr;

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

	void DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, CGeometryBuffer* vertexBuffer, CGeometryBuffer* indexBuffer);

	uint32 GetCurFrame();

	CRenderCommandMgr& GetRenderCommandMgr();

	CVertexFormatMgr& GetVertexFormatMgr();

	CGraphicResMgr& GetResMgr();
	
	CGraphicFactory& GetCraphicFactor();

	CRenderStateMgr& GetRenderStateMgr();

	void AddRef();

	void Release();

	uint32 GetRef();

	CTexture* CreateTextureFromFile(char* szFileName);

	std::string GetVertexShaderVersion();

	std::string GetPixelShaderVersion();

	CShader* CreateShaderFromFile(const char* szFileName, bool bVertexShader);

protected:	
	virtual bool CreateSuitableDevice();

	CRenderCommandMgr m_cRenderCommandMgr;
	CVertexFormatMgr m_cVertexFormatMgr;
	CGraphicResMgr m_ResMgr;
	CGraphicFactory* m_pGraphicFactory;
	CRenderStateMgr* m_pRenderStateMgr;

	CAlphaWindow* m_pWnd;
	float m_fHWVertexShaderVersion;
	float m_fHWPixelShaderVersion;
	uint8 m_nMaxSupportRenderTargetCnt;
	uint32 m_nCurFrame;

	uint32 m_nRef;
};