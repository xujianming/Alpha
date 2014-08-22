
#include "stdafx.h"
#include "CShader.h"

CShader::CShader( CGraphic* pGraphic ):
	CGraphicRes(m_pGraphic, ERT_Shader)
{

}

CShader::~CShader()
{

}

void CShader::SetParamData( const char* szName, const void* data, size_t size, EShaderDataType eDataType )
{
	SShaderParam& param = m_vecShaderParams[szName];
	assert(eDataType >= eSDT_Cnt);
	switch (eDataType)
	{
	case eSDT_4Bool:

		break;
	case eSDT_4Int32:
		break;
	case eSDT_4Float:
		break;
	case eSDT_Matrix:
		break;
	case eSDT_Texture:
		break;
	default:
		break;
	}
}

void CShader::SetParamMatrix( SShaderParam* pParam, matrix4x4f matrix )
{

}

void CShader::SetParamTexture( SShaderParam* pParam, CTexture* texture )
{

}

void CShader::AddParam( bool bVertexShader, const char* strName, uint32 nRegisterIndex, uint32 nRegisterCnt, EShaderDataType eDataType, const void* pDefaultValue, uint32 nCntPerReg, uint32 nRegPerElem, uint32 nElemCnt )
{
	for (uint32 i = 0; i < m_vecShaderParams.size(); i ++)
		if (m_vecShaderParams[i].m_pParam->m_strName == strName)
			return;
	m_vecShaderParams.push_back(SShaderActiveParam());
	SShaderActiveParam& param = *m_vecShaderParams.rbegin();
	if (bVertexShader)
	{
		param.m_nVertexRegisterIndex = nRegisterIndex;
		param.m_nVertexRegisterCnt = nRegisterCnt;
		param.m_nPixelRegisterIndex = INVALID_32BIT;
		param.m_nPixelRegisterCnt = 0;
	}
	else
	{
		param.m_nVertexRegisterIndex = INVALID_32BIT;
		param.m_nVertexRegisterCnt = 0;
		param.m_nPixelRegisterIndex = nRegisterIndex;
		param.m_nPixelRegisterCnt = nRegisterCnt;
	}
	param.m_pParam->m_strName = strName;
	param.m_pParam->m_nRegPerElem = nRegPerElem;
	param.m_pParam->m_nElemCnt = nElemCnt;
	if (eDataType < eSDT_Texture)
	{

	}
}

