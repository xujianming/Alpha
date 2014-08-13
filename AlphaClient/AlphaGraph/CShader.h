#pragma once

#include "CGraphicRes.h"

class CProgram
{

};

class CShader: public CGraphicRes
{
public:
	CShader(CGraphic* pGraphic);
	~CShader();
};