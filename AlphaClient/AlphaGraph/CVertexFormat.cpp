#include "stdafx.h"
#include <iostream>
#include "CVertexFormat.h"


CVertexFormat::CVertexFormat(CGraphic* pGraphic):m_pGraphic(pGraphic)
{

}

CVertexFormat::~CVertexFormat()
{

}

bool CVertexFormat::IsVertexFormat( SVertexElem* arrElem, uint16 elemCnt )
{
	if (m_nElemCnt != elemCnt)
		return false;
	for (uint8 i = 0; i < elemCnt; i ++)
	{
		if (!memcpy(&m_arrElem[arrElem[i].usage], &arrElem[i], sizeof(SVertexElem)))
			return false;
	}
	return true;
}

bool CVertexFormat::CreateVertexFormat( SVertexElem* arrElem, uint16 elemCnt )
{
	memset(m_arrElem, 0xffff, sizeof(m_arrElem));
	m_nElemCnt = elemCnt;
	for (uint8 i = 0; i < elemCnt; i ++)
	{
		m_arrElem[arrElem[i].usage] = arrElem[i];
	}
	return true;
}

const SVertexElem* CVertexFormat::GetVertexElemInfo()
{
	return m_arrElem;
}
