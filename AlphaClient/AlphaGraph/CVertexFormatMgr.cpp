#include "stdafx.h"
#include "CVertexFormatMgr.h"
#include "CVertexFormat.h"
#include "AlphaCommon\CAlphaCommonType.h"
#include <assert.h>

CVertexFormatMgr::CVertexFormatMgr( CGraphic* pGraphic )
{

}

CVertexFormatMgr::~CVertexFormatMgr()
{
	for (std::vector<CVertexFormat*>::iterator it = m_vecVertexFormats.begin(); it != m_vecVertexFormats.end(); it ++ )
		SAFE_DELETE(*it);
	m_vecVertexFormats.clear();
}

uint16 CVertexFormatMgr::AddVertexFormat( CVertexFormat* pVertexFormat )
{
	m_vecVertexFormats.push_back(pVertexFormat);
	return (uint16)m_vecVertexFormats.size() - 1;
}

uint16 CVertexFormatMgr::GetVertexFormat( SVertexElem* arrElem, uint16 elemCnt )
{
	for (uint16 i = 0; i < m_vecVertexFormats.size(); i ++)
		if (m_vecVertexFormats[i]->IsVertexFormat(arrElem, elemCnt))
			return i;
	return INVALID_16BIT;
}

CVertexFormat* CVertexFormatMgr::GetVertexFormat( uint16 nVertexFormat )
{
	assert(nVertexFormat < m_vecVertexFormats.size());
	return m_vecVertexFormats[nVertexFormat];
}
