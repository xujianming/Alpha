#pragma once
#include "AlphaCommon\TInvasiveList.h"

class CGraphicRes;


class CGraphicResMgr
{
public:
	CGraphicResMgr();
	virtual ~CGraphicResMgr();

	friend class CGraphicRes;

	void AddVedioMemSize(uint32 nMemSize);

private:
	TInvasiveList<CGraphicRes> m_ResList;
};