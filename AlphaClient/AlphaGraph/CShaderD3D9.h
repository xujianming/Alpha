#pragma once

#include "CShader.h"
#include <d3d9.h>
#include <d3dx9.h>

class CShaderD3D9: public CShader
{
public:
	CShaderD3D9(CGraphic* pGraphic);

	virtual ~CShaderD3D9();

	bool CreateShaderFromFile(const char* szFileName);
	
protected:

	void SetUpParamList(ID3DXConstantTable* pConstantTable, bool bVertexShader);

	ID3DXBuffer*		m_pShaderBuffer;
};