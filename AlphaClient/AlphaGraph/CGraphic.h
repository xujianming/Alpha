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

	void SetRenderTarget(CTexture* pRenderTarget, CTexture* pDepthpRenderTargets);

	void SetRenderTarget(CTexture* pRenderTargets[MAX_RENDER_TARGET], uint8 nCnt, CTexture* pDepthpRenderTargets);

	void DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex);

	void DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuffer, CGeometryBuffer* indexBuffer);

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

	CShader* CreateShaderFromFile(const char* szFileName);

	CTexture* GetBlankTexture() { return m_pBlankTexture; };

	uint16 CreateVertexFormat( SVertexElem* arrElem, uint16 cnt );

	CTexture* CGraphic::CreateRenderTarget( uint32 nWidth, uint32 nHeight, ETextureFormat eTargetFormat, int32 nMipMap, ETextureFormat eDepthStencilFormat );

	TVector2<uint32> GetClientSize();

	CTexture* GetMainRenderTarget()  { return m_pMainRenderTarget; }

	void SetView(const CMatrix& matView);

	const CMatrix& GetView();

	void SetProj(const CMatrix& matProj);

	const CMatrix& GetProj();

	void SetAmbient(const CVector4f& ambient);

	void SetDiffuse(const CVector4f& diffuse);

	void SetLigth(const SLight* arrLigth, uint8 nCnt);

	void AddLight(const SLight& light);

	void PopEnvir();

	void PushEnvir();

	void ClearRenderTarget(bool bClearTarget, bool bClearZBuffer, bool bClearStencil, uint32 nClearColor);

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

	CTexture* m_pMainRenderTarget;
	CTexture* m_pBlankTexture;
	uint32 m_nRef;
};