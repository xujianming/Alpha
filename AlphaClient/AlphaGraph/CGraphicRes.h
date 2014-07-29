#pragma once

#include "AlphaCommon\TInvasiveList.h"
#include "AlphaCommon\CAlphaCommonType.h"
#include "AlphaCommon\IAlphaUnknown.h"

class CGraphic;

class CGraphicRes: public TInvasiveNode<CGraphicRes>,
					public IAlphaUnknown
{
public:
	CGraphicRes(CGraphic* pGraphic);
	virtual ~CGraphicRes();

	void SetVedioMemSize(uint32 memSize);

	void AddRef();

	void Release();

private:

	void AddVedioMemSize();

	uint32 m_nVedioMemSize;

};