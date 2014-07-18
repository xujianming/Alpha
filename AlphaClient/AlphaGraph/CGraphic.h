#pragma once

#include "AlphaCommon\CAlphaCommonType.h"

class CAlphaWindow;
class CRenderCommandMgr;

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

protected:	
	virtual bool CreateSuitableDevice();

	CRenderCommandMgr* m_pRenderCommandMgr;
	CAlphaWindow* m_pWnd;
	float m_fHWVertexShaderVersion;
	float m_fHWPixelShaderVersion;
	uint8 m_nMaxSupportRenderTargetCnt;
};