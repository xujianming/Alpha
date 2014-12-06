#pragma once
#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
#include <vector>
#include "CTexture.h"

class CGraphic;
class CGeometryBuffer;

struct SFogInfo
{
	float fFar;
	float fNear;
	uint32 nColor;
};

struct SLight
{

};

struct SRenderTargetInfo
{
	CTexture* pRenderTargets[MAX_RENDER_TARGET];
	CTexture* pDepthpRenderTarget;
	SRenderTargetInfo()
	{
		memset(pRenderTargets, 0, sizeof(pRenderTargets));
		pDepthpRenderTarget = nullptr;
	}
};

struct SRenderEnvir
{
	enum { MAX_LIGHT = 8 };
	CVector4f ambient;
	CMatrix matView;
	CMatrix matViewInvert;
	CMatrix matProject;
	CMatrix matProjectInvert;
	CMatrix matViewProject;
	CVector4f viewPort;
	bool	 bFogEnable;
	SFogInfo fogInfo;
	bool	 bShadowMaskEnable;
	CTexture* pCurPeferredTarget;
	CVector4f scissor;
	CVector4f baseBrightness;
	uint8	 nLighCnt;
	SLight	 aryLight[MAX_LIGHT];
	CTexture* curShadowMap;
	SRenderTargetInfo renderTargetInfo;
};

struct SPrimiveInfo
{
	uint32 nPrimitiveCnt;
	uint32 nVertexCnt;
	uint32 nPrimitiveGroupCnt;
};

class CRenderCommandMgr
{
public:
	CRenderCommandMgr(CGraphic* pGraphic);
	
	~CRenderCommandMgr();
	
	const SRenderEnvir& GetCurEnvir() { return m_curEnvir; }

	void SetRenderTarget(CTexture* pRenderTargets[MAX_RENDER_TARGET], uint8 nCnt, CTexture* pDepthpRenderTargets);

	void DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex);
	
	void DrawPrimitive( const SMaterial& material, CMatrix* matWorld, uint16 nMatCnt, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint16 vertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf);
	
	void pushEnvir(SRenderEnvir envirState);
	
	void popEnvir();
	
	bool isEmpty();

	void SetView(const CMatrix& matView);

	const CMatrix& GetView();

	void SetProj(const CMatrix& matProj);

	const CMatrix& GetProj();

protected:
	SRenderEnvir m_curEnvir;
	std::vector<SRenderEnvir> m_envirStack;
	CGraphic* m_pGraphic; 
	SPrimiveInfo m_sPrimiveInfo;
};

