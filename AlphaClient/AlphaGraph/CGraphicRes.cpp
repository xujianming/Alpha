#include "stdafx.h"
#include <assert.h>
#include "CGraphicRes.h"
#include "CGraphicResMgr.h"
#include "CGraphic.h"

CGraphicRes::CGraphicRes( CGraphic* pGraphic, EResourceType eResType ):
	m_pGraphic(pGraphic),
	m_nUseFrame(0),
	m_eResType(ERT_Invalid),
	m_nVedioMemSize(0), 
	m_nRef(1)
{

}

CGraphicRes::~CGraphicRes()
{
	SetVedioMemSize(0);
	Remove();
}

CGraphicResMgr* CGraphicRes::GetResMgr()
{
	return &m_pGraphic->GetResMgr();
}

void CGraphicRes::SetVedioMemSize( uint32 nMemSize )
{
	if (nMemSize == m_nVedioMemSize)
		return;
	int32 dif = nMemSize - m_nVedioMemSize;
	AddVedioMemSize(dif);
}

void CGraphicRes::AddVedioMemSize( int32 nMemSize )
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
	m_nUseFrame = m_pGraphic->GetCurFrame();
	Remove();
	m_pGraphic->GetResMgr().m_ResList.PushBack(*this);
}

void CGraphicRes::OnRestore()
{

}

void CGraphicRes::OnLostDevice()
{
	OnFreeMemory();
}

void CGraphicRes::OnFreeMemory()
{

}

void CGraphicRes::AddRef()
{
	Use();
	m_nRef ++;
}

void CGraphicRes::Release()
{
	assert(m_nRef > 0);
	m_nRef --;
	if (!m_nRef)
	{
		Remove();
		delete this;
	}
}

uint32 CGraphicRes::GetRef()
{
	return m_nRef;
}
