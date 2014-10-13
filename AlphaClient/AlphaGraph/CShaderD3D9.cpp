#include "stdafx.h"
#include "CShaderD3D9.h"
#include "CGraphicD3D9.h"

CShaderD3D9::CShaderD3D9( CGraphic* pGraphic ):
	CShader(pGraphic),
	m_pShaderVertexShader(nullptr),
	m_pShaderPixelShader(nullptr)
{

}

CShaderD3D9::~CShaderD3D9()
{
	SAFE_RELEASE(m_pShaderVertexShader);
	SAFE_RELEASE(m_pShaderPixelShader);
}

bool CShaderD3D9::CreateShaderFromFile( const char* szFileName )
{
	ID3DXBuffer* pErrorBuffer = 0;
	ID3DXConstantTable* pConstantTable = nullptr;
	CGraphicD3D9* pGraphicD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	ID3DXBuffer* pBuffer = 0;
	HRESULT hr;

	hr = D3DXCompileShaderFromFile(szFileName, NULL, NULL, "VertexMain", D3DXGetVertexShaderProfile(pGraphicD3D9->GetDevice()), 0, &pBuffer, &pErrorBuffer, &pConstantTable);

	if (pErrorBuffer)
	{
		::MessageBox(0, (char*)pErrorBuffer->GetBufferPointer(), 0, 0);
		SAFE_RELEASE(pErrorBuffer);
	}
	if (hr != D3D_OK)
		return false;

	hr = pGraphicD3D9->GetDevice()->CreateVertexShader((DWORD*)pBuffer->GetBufferPointer(), &m_pShaderVertexShader);
	
	if (hr != D3D_OK)
		return false;

	SetUpParamList(pConstantTable, true);
	SAFE_RELEASE(pConstantTable);

	hr = D3DXCompileShaderFromFile(szFileName, NULL, NULL, "PixelMain", D3DXGetPixelShaderProfile(pGraphicD3D9->GetDevice()), 0, &pBuffer, &pErrorBuffer, &pConstantTable);
	if (pErrorBuffer)
	{
		::MessageBox(0, (char*)pErrorBuffer->GetBufferPointer(), 0, 0);
		SAFE_RELEASE(pErrorBuffer);
	}
	if (hr != D3D_OK)
		return false;
	
	hr = pGraphicD3D9->GetDevice()->CreatePixelShader((DWORD*)pBuffer->GetBufferPointer(), &m_pShaderPixelShader);

	if (hr != D3D_OK)
		return false;

	SetUpParamList(pConstantTable, false);
	SAFE_RELEASE(pConstantTable);

	return true;
}

void CShaderD3D9::SetUpParamList(ID3DXConstantTable* pConstantTable, bool bVertexShader)
{
	D3DXCONSTANTTABLE_DESC desc;
	pConstantTable->GetDesc(&desc);

	for (uint32 i = 0; i < desc.Constants; i ++)
	{
		D3DXHANDLE handle;
		handle = pConstantTable->GetConstant(NULL, i);
		D3DXCONSTANT_DESC constDesc[256];
		uint32 Cnt = 256;
		pConstantTable->GetConstantDesc(handle, constDesc, &Cnt);
		
		if (constDesc[0].RegisterSet == D3DXRS_SAMPLER)
		{
			assert (constDesc[0].Type >= D3DXPT_SAMPLER1D);
			AddParam(bVertexShader, constDesc[0].Name, constDesc[0].RegisterIndex, constDesc[0].RegisterCount, 
			EShaderDataType(constDesc[0].Type - D3DXPT_SAMPLER1D + eSDT_Texture), constDesc[0].DefaultValue, 1, 1, 1);
		}
		else if (constDesc[0].Class == D3DXPC_MATRIX_COLUMNS)
			AddParam(bVertexShader, constDesc[0].Name, constDesc[0].RegisterIndex, constDesc[0].RegisterCount,
			EShaderDataType(constDesc[0].RegisterSet), constDesc[0].DefaultValue, 4, constDesc[0].Columns, constDesc[0].Elements);
		else if (constDesc[0].Class == D3DXPC_MATRIX_ROWS)
			AddParam(bVertexShader, constDesc[0].Name, constDesc[0].RegisterIndex, constDesc[0].RegisterCount,
			EShaderDataType(constDesc[0].RegisterSet), constDesc[0].DefaultValue, 4, constDesc[0].Rows, constDesc[0].Elements);
		else if (constDesc[0].Columns > 4)
			AddParam(bVertexShader, constDesc[0].Name, constDesc[0].RegisterIndex, constDesc[0].RegisterCount,
			EShaderDataType(constDesc[0].RegisterSet), constDesc[0].DefaultValue, 4, 1, constDesc[0].Elements);
		else
			AddParam(bVertexShader, constDesc[0].Name, constDesc[0].RegisterIndex, constDesc[0].RegisterCount,
			EShaderDataType(constDesc[0].RegisterSet), constDesc[0].DefaultValue, constDesc[0].Columns, constDesc[0].Rows, constDesc[0].Elements);

	}
}

