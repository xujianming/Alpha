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
	
	IDirect3DVertexShader9* GetVertexShader() { return m_pShaderVertexShader; }

	IDirect3DPixelShader9* GetPixelShader() { return m_pShaderPixelShader; }

protected:

	void SetUpParamList(ID3DXConstantTable* pConstantTable, bool bVertexShader);

	IDirect3DVertexShader9*		m_pShaderVertexShader;
	IDirect3DPixelShader9*		m_pShaderPixelShader;


};