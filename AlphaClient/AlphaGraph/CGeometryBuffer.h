#pragma once

#include "CGraphicRes.h"

#define INVLAID_BUFFER (tByte*)INVALID_32BIT

class CGraphic;

class CGeometryBuffer: public CGraphicRes
{
public:
	CGeometryBuffer(CGraphic* pGraphic, EResourceType eResType);

	virtual ~CGeometryBuffer();

	virtual bool Lock(bool bDiscard);

	virtual void UnLock() = 0;

	bool IsStatic();

	virtual bool IsVertexBuffer() = 0;

	virtual void FillBuffer(uint32 startPos, void *pBuffer, uint32 nBufferSize);

	virtual bool Create(uint32 nStride, uint32 nCnt, bool bStatic);

	virtual void OnFreeMemory();

	virtual bool IsDataCommitted();

	uint32 GetSzie();

	uint32 GetStride()	{ return m_nStride; }

protected:
	virtual bool CheckBuffer() = 0;
	
	CGraphic* m_pGraphic;
	bool m_bStatic;
	uint32 m_nStride;
	uint32 m_nBufferSize;
	tByte *m_pLockBuffer;
};