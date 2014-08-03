#pragma once

#include "AlphaCommon\AlphaCommonType.h"
#include <vector>
#include "GraphicHelp.h"

class CVertexFormat;
class CGraphic;

class CVertexFormatMgr
{
public:
	CVertexFormatMgr(CGraphic* pGraphic);
	virtual ~CVertexFormatMgr();

	uint16 AddVertexFormat(CVertexFormat* pVertexFormat);
	uint16 GetVertexFormat(SVertexElem* arrElem, uint16 cnt);
	CVertexFormat* GetVertexFormat(uint16 nVertexFormat);

private:
	CGraphic* m_pGraphic;
	std::vector<CVertexFormat*> m_vecVertexFormats;
};