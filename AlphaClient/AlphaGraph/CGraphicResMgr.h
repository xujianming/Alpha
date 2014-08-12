#pragma once
#include "AlphaCommon\TInvasiveList.h"
#include "AlphaCommon\AlphaCommonType.h"
#include "CGraphicRes.h"

class CGraphic;

class CGraphicResMgr
{
public:
	CGraphicResMgr(CGraphic* pGraphic);
	virtual ~CGraphicResMgr();

	friend class CGraphicRes;

	void AddVedioMemSize(uint32 nMemSize);

	void Clear();

	void InvalidRes();

	void RestoreRes();

private:
	CGraphic* m_pGraphic;
	uint32 m_nCurVedioMemSize;
	uint32 m_nMaxVedioMemSize;
	TInvasiveList<CGraphicRes> m_ResList;
};