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
	CTexture* CurRenderTarget;
	CVector4f scissor;
	CVector4f baseBrightness;
	uint8	 nLighCnt;
	SLight	 aryLight[MAX_LIGHT];
	CTexture* CurShadowMap;
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
	void DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexFormat, uint16 vertexStride, const void* arrVertex, const void* arrIndex);
	void DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexFormat, CGeometryBuffer* vertexBuf, CGeometryBuffer* indexBuf);
	void pushEnvir(SRenderEnvir envirState);
	void popEnvir();
	bool isEmpty();
protected:
	SRenderEnvir m_curEnvir;
	std::vector<SRenderEnvir> m_envirStack;
	CGraphic* m_pGraphic; 
	SPrimiveInfo m_sPrimiveInfo;
};

