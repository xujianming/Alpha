#pragma once

#include "GraphicHelp.h"

class CVertexFormat
{
public:
	CVertexFormat();
	virtual ~CVertexFormat();

	bool IsVertexFormat(SVertexElem* arrElem, uint8 elemCnt);

	void CreateVertexFormat(SVertexElem* arrElem, uint8 elemCnt);

	const SVertexElem* GetVertexElemInfo();

protected:
	SVertexElem m_arrElem[EDT_Cnt];
	uint8 m_nElemCnt;
};