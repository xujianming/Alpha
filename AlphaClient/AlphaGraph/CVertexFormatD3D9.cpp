#include "stdafx.h"
#include "CVertexFormatD3D9.h"
#include "CGraphicD3D9.h"
#include <vector>

CVertexFormatD3D9::CVertexFormatD3D9( CGraphic* pGraphic ):
	CVertexFormat(pGraphic),
	m_pDeclaration(nullptr)
{

}

CVertexFormatD3D9::~CVertexFormatD3D9()
{

}

bool CVertexFormatD3D9::CreateVertexFormat(SVertexElem* arrElem, uint16 elemCnt)
{
	uint8 arrDeclareUsg[eDU_Cnt][2] = 
	{
		{ D3DDECLUSAGE_POSITION	,	0 },
		{ D3DDECLUSAGE_COLOR	,	0 },
		{ D3DDECLUSAGE_COLOR	,	1 },
		{ D3DDECLUSAGE_NORMAL	,	0 },
		{ D3DDECLUSAGE_TEXCOORD	,	0 },
		{ D3DDECLUSAGE_TEXCOORD	,	1 },
		{ D3DDECLUSAGE_TEXCOORD	,	2 },
		{ D3DDECLUSAGE_TEXCOORD	,	3 },
		{ D3DDECLUSAGE_TEXCOORD	,	4 },
		{ D3DDECLUSAGE_TEXCOORD	,	5 },
		{ D3DDECLUSAGE_TEXCOORD	,	6 },
		{ D3DDECLUSAGE_TEXCOORD	,	7 }
	};

	uint8 arrDeclareType[eDT_Cnt] =
	{
		D3DDECLTYPE_FLOAT1,
		D3DDECLTYPE_FLOAT2,
		D3DDECLTYPE_FLOAT3,
		D3DDECLTYPE_FLOAT4,
		D3DDECLTYPE_UBYTE4N,
	};
	D3DVERTEXELEMENT9 endElement = D3DDECL_END();
	std::vector<D3DVERTEXELEMENT9> vecD3DElements(elemCnt + 1, endElement);
	for (uint16 i = 0; i < elemCnt; i ++)
	{
		vecD3DElements[i].Stream = 0;
		vecD3DElements[i].Offset = arrElem[i].offset;
		vecD3DElements[i].Method = D3DDECLMETHOD_DEFAULT;
		vecD3DElements[i].Type = arrDeclareType[arrElem[i].type];
		vecD3DElements[i].Usage = arrDeclareUsg[arrElem[i].usage][0];
		vecD3DElements[i].UsageIndex = arrDeclareUsg[arrElem[i].usage][1];
	}

	CGraphicD3D9* pGraphD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	if (FAILED(pGraphD3D9->GetDevice()->CreateVertexDeclaration(&vecD3DElements[0], &m_pDeclaration)))
		return false;

	return CVertexFormat::CreateVertexFormat(arrElem, elemCnt);
}

IDirect3DVertexDeclaration9* CVertexFormatD3D9::GetVertexDeclaration()
{
	return m_pDeclaration;
}

