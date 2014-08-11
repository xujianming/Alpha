#pragma once

class CGraphic;
class CVertexFormat;
class CTexture;
class CGeometryBuffer;

class CGraphicFactory
{
public:
	CGraphicFactory( CGraphic* pGraphic );
	virtual ~CGraphicFactory();

	virtual CVertexFormat* CreateVertexFormat() = 0;

	virtual CTexture* CreateTexture() = 0;

	virtual CGeometryBuffer* CreateVertexBuffer() = 0;

	virtual CGeometryBuffer* CreateIndexBuffer() = 0;

};