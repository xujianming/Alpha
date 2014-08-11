#pragma once

#include "CGraphicFactory.h"

class CGraphicFactoryD3D9: public CGraphicFactory
{
public:
	CGraphicFactoryD3D9( CGraphic* pGraphic );
	~CGraphicFactoryD3D9();

	virtual CVertexFormat* CreateVertexFormat();

	virtual CTexture* CreateTexture();

	virtual CGeometryBuffer* CreateVertexBuffer();

	virtual CGeometryBuffer* CreateIndexBuffer();

};