#include "stdafx.h"
#include "CGeometryBufferD3D9.h"
#include "CGraphicD3D9.h"

CGeometryBufferD3D9::CGeometryBufferD3D9( CGraphic* pGraphic, EResourceType eResType ):
	CGeometryBuffer(pGraphic, eResType),
	m_pD3DBuffer(nullptr)
{

}

IDirect3DResource9* CGeometryBufferD3D9::GetD3DBuffer()
{
	Use();
	UnLock();
	return m_pD3DBuffer;
}

void CGeometryBufferD3D9::OnFreeMemory()
{
	if (!m_pD3DBuffer)
		return;
	CGeometryBuffer::OnFreeMemory();
	SAFE_RELEASE(m_pD3DBuffer);
}

CVertexBufferD3D9::CVertexBufferD3D9( CGraphic* pGraphic ):
	CGeometryBufferD3D9(pGraphic, ERT_VertexBuffer)
{

}

bool CVertexBufferD3D9::Lock( bool bDiscard )
{
	if (!CGeometryBufferD3D9::Lock(bDiscard))
		return false;
	;
	if ((m_pLockBuffer == nullptr || m_pLockBuffer == INVLAID_BUFFER) && 
		FAILED(static_cast<IDirect3DVertexBuffer9*>(m_pD3DBuffer)->Lock(0, 0, 
			(void**)&m_pLockBuffer, bDiscard ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE)))
	{
		m_pLockBuffer = INVLAID_BUFFER;
		return false;
	}
	return true;
}

void CVertexBufferD3D9::UnLock()
{
	if (m_pLockBuffer == nullptr || m_pLockBuffer == INVLAID_BUFFER)
		return;
	static_cast<IDirect3DVertexBuffer9*>(m_pD3DBuffer)->Unlock();
	m_pLockBuffer = nullptr;
}

bool CVertexBufferD3D9::CheckBuffer()
{
	if (m_pD3DBuffer)
		return true;
	CGraphicD3D9* pGraphicD3D = static_cast<CGraphicD3D9*>(m_pGraphic);
	HRESULT result = pGraphicD3D->GetDevice()->CreateVertexBuffer(m_nBufferSize, 
		D3DUSAGE_WRITEONLY | (m_bStatic ? 0 : D3DUSAGE_DYNAMIC), 0, D3DPOOL_DEFAULT,
		(IDirect3DVertexBuffer9**)&m_pD3DBuffer, nullptr);
	if (FAILED(result))
		return false;
	AddVedioMemSize(m_nBufferSize);
	m_pLockBuffer = INVLAID_BUFFER;
	return true;
}

CIndexBufferD3D9::CIndexBufferD3D9( CGraphic* pGraphic ):
	CGeometryBufferD3D9(pGraphic, ERT_IndexBuffer)
{

}

bool CIndexBufferD3D9::Lock( bool bDiscard )
{
	if (!CGeometryBufferD3D9::Lock(bDiscard))
		return false;
	;
	if ((m_pLockBuffer == nullptr || m_pLockBuffer == INVLAID_BUFFER) && 
		FAILED(static_cast<IDirect3DIndexBuffer9*>(m_pD3DBuffer)->Lock(0, 0, 
		(void**)&m_pLockBuffer, bDiscard ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE)))
	{
		m_pLockBuffer = INVLAID_BUFFER;
		return false;
	}
	return true;
}

void CIndexBufferD3D9::UnLock()
{
	if (m_pLockBuffer == nullptr || m_pLockBuffer == INVLAID_BUFFER)
		return;
	static_cast<IDirect3DIndexBuffer9*>(m_pD3DBuffer)->Unlock();
	m_pLockBuffer = nullptr;
}

bool CIndexBufferD3D9::CheckBuffer()
{
	if (m_pD3DBuffer)
		return true;
	CGraphicD3D9* pGraphicD3D = static_cast<CGraphicD3D9*>(m_pGraphic);
	HRESULT result = pGraphicD3D->GetDevice()->CreateIndexBuffer(m_nBufferSize, 
		D3DUSAGE_WRITEONLY | (m_bStatic ? 0 : D3DUSAGE_DYNAMIC), D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		(IDirect3DIndexBuffer9**)&m_pD3DBuffer, nullptr);
	if (FAILED(result))
		return false;
	AddVedioMemSize(m_nBufferSize);
	m_pLockBuffer = INVLAID_BUFFER;
	return true;
}
