#include "stdafx.h"
#include "CGeometryBuffer.h"
#include <iostream>
#include <assert.h>

CGeometryBuffer::CGeometryBuffer( CGraphic* pGraphic, EResourceType eResType ):
	CGraphicRes(pGraphic, eResType),
	m_bStatic(false),
	m_nBufferSize(0),
	m_nStride(0),
	m_pLockBuffer(INVLAID_BUFFER)
{

}

CGeometryBuffer::~CGeometryBuffer()
{
	OnFreeMemory();
}

bool CGeometryBuffer::IsStatic()
{
	return m_bStatic;
}

void CGeometryBuffer::FillBuffer( uint32 startPos, void *pBuffer, uint32 nBufferSize )
{
	assert(startPos + nBufferSize <= m_nBufferSize);
	memcpy(m_pLockBuffer + startPos, pBuffer, nBufferSize);
}

bool CGeometryBuffer::Create( uint32 nStride, uint32 nCnt, bool bStatic )
{
	m_nBufferSize = nStride * nCnt;
	m_bStatic = bStatic;
	m_nStride = nStride;
	return CheckBuffer();
}

uint32 CGeometryBuffer::GetSzie()
{
	return m_nBufferSize;
}

void CGeometryBuffer::OnFreeMemory()
{
	UnLock();
	assert (m_nBufferSize == m_nVedioMemSize);
	AddVedioMemSize(-m_nBufferSize);
	m_pLockBuffer = (tByte*)INVALID_32BIT;
}

bool CGeometryBuffer::IsDataCommitted()
{
	return m_pLockBuffer == nullptr;
}

bool CGeometryBuffer::Lock( bool bDiscard )
{
	if (!CheckBuffer())
		return false;
	return true;
}
