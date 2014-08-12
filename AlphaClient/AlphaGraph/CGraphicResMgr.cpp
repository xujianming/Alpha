#include "stdafx.h"
#include "CGraphicResMgr.h"
#include <vector>
#include "CGraphic.h"


CGraphicResMgr::CGraphicResMgr(CGraphic* pGraphic): 
	m_pGraphic(pGraphic),
	m_nCurVedioMemSize(0),
	m_nMaxVedioMemSize(100 * 1024 * 1024)
{

}

CGraphicResMgr::~CGraphicResMgr()
{

}

void CGraphicResMgr::AddVedioMemSize( uint32 nMemSize )
{
	m_nCurVedioMemSize += nMemSize;

	//显存不够，释放十帧前分配的资源
	for (CGraphicRes* res = m_ResList.GetFirst(); res; res = res->Next())
	{
		if (m_nCurVedioMemSize < m_nMaxVedioMemSize)
			break;
		if (res->GetUseFrame() + 10 < m_pGraphic->GetCurFrame())
			res->OnFreeMemory();
	}
}

void CGraphicResMgr::Clear()
{
	while (m_ResList.GetFirst())
		delete m_ResList.GetFirst();
}

void CGraphicResMgr::InvalidRes()
{
	std::vector<CGraphicRes*> vecRes;
	for (CGraphicRes* res = m_ResList.GetFirst(); res; res = res->Next())
		vecRes.push_back(res);
	std::vector<CGraphicRes*>::iterator it;
	for (it = vecRes.begin(); it != vecRes.end(); it ++)
		(*it)->AddRef();
	for (it = vecRes.begin(); it != vecRes.end(); it ++)
		(*it)->OnLostDevice();
	for (it = vecRes.begin(); it != vecRes.end(); it ++)
		(*it)->Release();
}

void CGraphicResMgr::RestoreRes()
{
	std::vector<CGraphicRes*> vecRes;
	for (CGraphicRes* res = m_ResList.GetFirst(); res; res = res->Next())
		vecRes.push_back(res);
	std::vector<CGraphicRes*>::iterator it;
	for (it = vecRes.begin(); it != vecRes.end(); it ++)
		(*it)->AddRef();
	for (it = vecRes.begin(); it != vecRes.end(); it ++)
		(*it)->OnRestore();
	for (it = vecRes.begin(); it != vecRes.end(); it ++)
		(*it)->Release();
}
