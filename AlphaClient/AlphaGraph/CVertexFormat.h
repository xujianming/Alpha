#pragma once
#include "AlphaCommon\AlphaCommonType.h"
#include "GraphicHelp.h"
class CGraphic;
class CVertexFormat
{
public:
	CVertexFormat(CGraphic* pGraphic);
	virtual ~CVertexFormat();

	bool IsVertexFormat(SVertexElem* arrElem, uint8 elemCnt);

	virtual bool CreateVertexFormat(SVertexElem* arrElem, uint8 elemCnt);

	const SVertexElem* GetVertexElemInfo();

protected:
	SVertexElem m_arrElem[eDT_Cnt];
	uint8 m_nElemCnt;
	CGraphic* m_pGraphic;
};