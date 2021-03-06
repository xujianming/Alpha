#pragma once

#include <d3d9.h>

#include "CVertexFormat.h"

class CVertexFormatD3D9: public CVertexFormat
{
public:
	CVertexFormatD3D9(CGraphic* pGraphic);
	~CVertexFormatD3D9();

	virtual bool CreateVertexFormat(SVertexElem* arrElem, uint16 elemCnt);
	IDirect3DVertexDeclaration9* GetVertexDeclaration();
protected:
	IDirect3DVertexDeclaration9* m_pDeclaration;
};