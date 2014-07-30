#include "stdafx.h"
#include <assert.h>
#include "CGraphicRes.h"
#include "CGraphicResMgr.h"
#include "CGraphic.h"

CGraphicRes::CGraphicRes( CGraphic* pGraphic ):
	m_pGraph(pGraphic),
	m_nUseFrame(0),
	m_eResType(ERT_Invalid),
	m_nVedioMemSize(0)
{

}

CGraphicRes::~CGraphicRes()
{

}

CGraphicResMgr* CGraphicRes::GetResMgr()
{
	return &m_pGraph->GetResMgr();
}

void CGraphicRes::SetVedioMemSize( uint32 nMemSize )
{
	if (nMemSize == m_nVedioMemSize)
		return;
	int32 dif = nMemSize - m_nVedioMemSize;
	AddVedioMemSize(dif);
}

void CGraphicRes::AddVedioMemSize( uint32 nMemSize )
{
	assert( m_nVedioMemSize + nMemSize >= 0);
	m_nVedioMemSize = m_nVedioMemSize + nMemSize;
	Use();
	GetResMgr()->AddVedioMemSize(nMemSize);
}

EResourceType CGraphicRes::GetResType()
{
	return m_eResType;
}

uint32 CGraphicRes::GetUseFrame()
{
	return m_nUseFrame;
}

void CGraphicRes::Use()
{
	m_nUseFrame = m_pGraph->GetCurFrame();
	Remove();
	m_pGraph->GetResMgr().m_ResList.PushBack(*this);
}
