#pragma once
#include "AlphaCommon\AlphaCommonType.h"
#include "GraphicHelp.h"
class CGraphic;
class CVertexFormat
{
public:
	CVertexFormat(CGraphic* pGraphic);
	virtual ~CVertexFormat();

	bool IsVertexFormat(SVertexElem* arrElem, uint16 elemCnt);

	virtual bool CreateVertexFormat(SVertexElem* arrElem, uint16 elemCnt);

	const SVertexElem* GetVertexElemInfo();

protected:
	SVertexElem m_arrElem[eDU_Cnt];
	uint16 m_nElemCnt;
	CGraphic* m_pGraphic;
};