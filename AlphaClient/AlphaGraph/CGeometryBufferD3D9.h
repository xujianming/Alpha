#pragma once

#include <d3d9.h>
#include "CGeometryBuffer.h"


class CGeometryBufferD3D9: public CGeometryBuffer
{
public:
	CGeometryBufferD3D9(CGraphic* pGraphic, EResourceType eResType);

	virtual void OnFreeMemory();

	IDirect3DResource9* GetD3DBuffer();

protected:
	IDirect3DResource9* m_pD3DBuffer;
};

class CVertexBufferD3D9: public CGeometryBufferD3D9
{
public:
	CVertexBufferD3D9(CGraphic* pGraphic);

	bool IsVertexBuffer() { return true; }

	bool Lock(bool bDiscard);

	void UnLock();

protected:
	bool CheckBuffer();
};

class CIndexBufferD3D9: public CGeometryBufferD3D9
{
public:
	CIndexBufferD3D9(CGraphic* pGraphic);

	bool IsVertexBuffer() { return false; }

	bool Lock(bool bDiscard);

	void UnLock();

protected:
	bool CheckBuffer();
};