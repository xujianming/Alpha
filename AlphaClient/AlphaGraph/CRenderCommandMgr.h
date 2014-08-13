#pragma once
#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
#include <vector>
#include "CTexture.h"
class CGraphic;

struct SFogInfo
{
	float fFar;
	float fNear;
	vector4f color;
};

struct SRenderEnvir
{
	uint8	 nMaxLight;
	vector4f ambient;
	vector4f matView;
	vector4f matViewInvert;
	vector4f matProject;
	vector4f matProjectInvert;
	vector4f viewPort;
	bool	 bFogEnable;
	SFogInfo fogInfo;
	bool	 bShadowMaskEnable;
	CTexture* pCurPeferredTarget;
	CTexture* CurRenderTarget;
	vector4f scissor;
	vector4f baseBrightness;
	uint8	 nLighCnt;
	//SLight	 aryLight[];
	CTexture* CurShadowMap;
};

struct SPrimiveInfo
{
	uint32 nPrimiveCnt;
	uint32 nTriangleCnt;
};

class CRenderCommandMgr
{
public:
	CRenderCommandMgr(CGraphic* pGraph);
	~CRenderCommandMgr();
	void DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex);
	void pushEnvir(SRenderEnvir envirState);
	void popEnvir();
	bool isEmpty();
protected:
	SRenderEnvir m_curEnvir;
	std::vector<SRenderEnvir> m_envirStack;
};

