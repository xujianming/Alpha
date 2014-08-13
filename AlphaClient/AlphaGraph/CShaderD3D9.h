#pragma once

#include "CShader.h"

class CShaderD3D9: public CShader
{
public:
	CShaderD3D9(CGraphic* pGraphic);
	virtual ~CShaderD3D9();
};