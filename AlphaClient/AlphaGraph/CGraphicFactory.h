#pragma once

class CGraphic;
class CVertexFormat;


class CGraphicFactory
{
public:
	CGraphicFactory( CGraphic* pGraphic );
	virtual ~CGraphicFactory();

	virtual CVertexFormat* CreateVertexFormat() = 0;

};