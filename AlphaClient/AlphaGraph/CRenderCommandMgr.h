#pragma once
#include "SMaterial.h"
#include "GraphicHelp.h"
#include "AlphaCommon\CAlphaCommonType.h"
#include <vector>
class CGraphicD3D9;

struct SRenderEnvir
{

};

class CRenderCommandMgr
{
public:
	CRenderCommandMgr(CGraphicD3D9* pGraph);
	~CRenderCommandMgr();
	void DrawPrimitive( const SMaterial& material, EPrimitiveType primitiveType, uint16 vertexCnt, uint16 primitiveCnt, uint8 vertexType, uint16 vertexStride, const void* arrVertex, const void* arrIndex);
	void pushEnvir(SRenderEnvir envirState);
	void popEnvir();
	void isEmpty();
protected:
	SRenderEnvir m_curEnvir;
	std::vector<SRenderEnvir> m_envirStack;
};

