
#include "stdafx.h"
#include "CShader.h"

CShader::CShader( CGraphic* pGraphic ):
	CGraphicRes(pGraphic, ERT_Shader)
{

}

CShader::~CShader()
{
	for (uint32 i = 0; i < m_vecShaderParams.size(); i ++)
		SAFE_DELETE(m_vecShaderParams[i]);
}

void CShader::SetParamData( uint8 nIndex, const void* data, size_t size, EShaderDataType eDataType )
{
	if (nIndex > m_vecShaderParams.size())
		return;
	SShaderActiveParam& param = *m_vecShaderParams[nIndex];
	assert(eDataType < eSDT_Cnt);
	switch (eDataType)
	{
	case eSDT_4Bool:
		SetParamVector4(param, (TVector4<bool>*)data, size / sizeof(TVector4<bool>));
		break;
	case eSDT_4Int32:
		SetParamVector4(param, (TVector4<int32>*)data, size / sizeof(TVector4<int32>));
		break;
	case eSDT_4Float:
		SetParamVector4(param, (TVector4<float>*)data, size / sizeof(TVector4<float>));
		break;
	case eSDT_Matrix:
		SetParamMatrix(param, (CMatrix*)data, size / sizeof(CMatrix));
		break;
	case eSDT_Texture:
		SetParamTexture(param, (CTexture*)data);
		break;
	default:
		break;
	}
}

void CShader::SetParamData( const char* szParamName, const void* data, size_t size, EShaderDataType eDataType )
{
	uint8 index = GetParamIndex(szParamName);
	if (index != INVALID_8BIT)
		SetParamData(index, data, size, eDataType);
}

void CShader::SetParamMatrix(SShaderActiveParam& sParam, const CMatrix* matrix, uint32 nElemCnt)
{
	assert(sParam.m_nRegPerElem > 1);
	nElemCnt = min(nElemCnt, sParam.m_nElemCnt);
	CVector4f* pDes = (CVector4f*)&sParam.m_strBuffer[0];
	for (uint32 i = 0; i < nElemCnt; i ++)
		for (uint32 j = 0; j < sParam.m_nRegPerElem; j ++)
			memcpy(pDes ++, &matrix[i][j], sizeof(CVector4f));
}

void CShader::SetParamTexture(SShaderActiveParam& sParam, CTexture* texture )
{
	if (sParam.m_nElemCnt == 0)
		return;
	assert(sParam.m_eDataType >= eSDT_Texture);
	SShaderTextureState* pDes = (SShaderTextureState*)&sParam.m_strBuffer[0];
	pDes->m_pTexture = texture;
}

void CShader::AddParam( bool bVertexShader, const char* strName, uint32 nRegisterIndex, uint32 nRegisterCnt, EShaderDataType eDataType, const void* pDefaultValue, uint32 nCntPerReg, uint32 nRegPerElem, uint32 nElemCnt )
{
	for (uint32 i = 0; i < m_vecShaderParams.size(); i ++)
		if (m_vecShaderParams[i]->m_strName == strName)
			return;
	m_vecShaderParams.push_back(new SShaderActiveParam());
	SShaderActiveParam* pParam = *m_vecShaderParams.rbegin();
	if (bVertexShader)
	{
		pParam->m_nVertexRegisterIndex = nRegisterIndex;
		pParam->m_nVertexRegisterCnt = nRegisterCnt;
		pParam->m_nPixelRegisterIndex = INVALID_32BIT;
		pParam->m_nPixelRegisterCnt = 0;
	}
	else
	{
		pParam->m_nVertexRegisterIndex = INVALID_32BIT;
		pParam->m_nVertexRegisterCnt = 0;
		pParam->m_nPixelRegisterIndex = nRegisterIndex;
		pParam->m_nPixelRegisterCnt = nRegisterCnt;
	}

	pParam->m_eDataType = eDataType;
	pParam->m_strName = strName;
	pParam->m_nRegPerElem = nRegPerElem;
	pParam->m_nElemCnt = nElemCnt;
	pParam->m_strBuffer.resize(nRegPerElem * nElemCnt * sizeof(TVector4<float>));

	if (pDefaultValue && eDataType < eSDT_Texture)
	{
		uint32 nStride = eDataType == eSDT_4Bool ? sizeof(bool) : sizeof(float);
		TVector4<float>* pRegister = (TVector4<float>*)&pParam->m_strBuffer[0];
		const tByte* pSrc = (const tByte*)pDefaultValue;
		for (uint32 nDes = 0; nDes < nRegisterCnt; nDes ++, pSrc += nStride * nCntPerReg)
		{
			switch (eDataType)
			{
			case eSDT_4Bool:
				memcpy(&pRegister[nDes], &(TVector4<float>(*(TVector4<bool>*)pSrc)), nStride * nCntPerReg);
				break;
			case eSDT_4Int32:
				memcpy(&pRegister[nDes], &(TVector4<float>(*(TVector4<int32>*)pSrc)), nStride * nCntPerReg);
				break;
			case eSDT_4Float:
				memcpy(&pRegister[nDes], &(TVector4<float>(*(TVector4<float>*)pSrc)), nStride * nCntPerReg);
				break;
			case eSDT_Matrix:
				assert("do not support matrix");
				break;
			default:
				break;
			}
		}
	}
	else if (eDataType >= eSDT_Texture)
	{
		if (pDefaultValue)
			pParam->m_strBuffer.assign((const char*)pDefaultValue, sizeof(SSampleState));
		else
			pParam->m_strBuffer.resize(sizeof(SSampleState));
	}

	if (eDataType < eSDT_Texture)
		m_vecVectorParams.push_back(pParam);
	else
		m_vecSampleParams.push_back(pParam);
}

uint8 CShader::GetParamIndex( const char* szParamName )
{
	for (uint32 i = 0; i < m_vecShaderParams.size(); i ++)
		if (m_vecShaderParams[i]->m_strName == szParamName)
			return i;
	return INVALID_8BIT;
}

void CShader::SetShaderParam( const SMaterial& sMaterial,const SRenderEnvir& sEnvir, const CMatrix* arrMatrix, uint8 nMatrixCnt )
{
	CMatrix matWorld;
	if (arrMatrix)
		SetParamData("matWorld", arrMatrix, nMatrixCnt * sizeof(CMatrix), eSDT_Matrix);
	else
		SetParamData("matWorld", &matWorld, sizeof(CMatrix), eSDT_Matrix);

	const CMatrix& matView = sEnvir.matView;
	if (arrMatrix)
	{
		CMatrix matWorldView[256];
		for (uint8 i = 0; i < nMatrixCnt; i ++)
			matWorldView[i] = arrMatrix[i] * matView;
		SetParamData("matWorldView", arrMatrix, nMatrixCnt * sizeof(CMatrix), eSDT_Matrix);
	}
	else
		SetParamData("matWorldView", &matView, sizeof(CMatrix), eSDT_Matrix);

	const CMatrix& matViewProject = sEnvir.matViewProject;
	if (arrMatrix)
	{
		CMatrix matWorldViewProject[256];
		for (uint8 i = 0; i < nMatrixCnt; i ++)
			matWorldViewProject[i] = arrMatrix[i] * matViewProject;
		SetParamData("matWorldViewProject", arrMatrix, nMatrixCnt * sizeof(CMatrix), eSDT_Matrix);
	}
	else
		SetParamData("matWorldViewProject", &matViewProject, sizeof(CMatrix), eSDT_Matrix);

	SetParamData("matView", &sEnvir.matView, sizeof(CMatrix), eSDT_Matrix);
	SetParamData("matProject", &sEnvir.matProject, sizeof(CMatrix), eSDT_Matrix);
}

