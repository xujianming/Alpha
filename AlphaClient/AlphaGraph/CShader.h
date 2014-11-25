#pragma once

#include <string>
#include <vector>
#include "AlphaCommon\TVector.h"
#include "CGraphicRes.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
#include "SMaterial.h"
#include "CRenderCommandMgr.h"

using namespace std;

class CTexture;

enum EShaderDataType
{
	eSDT_4Bool,
	eSDT_4Int32,
	eSDT_4Float,
	eSDT_Matrix,
	eSDT_Texture,
	eSDT_Cnt,
};

struct SShaderTextureState
{
	CTexture* m_pTexture;
	SSampleState* m_pSampleState;
	SShaderTextureState(): 
		m_pTexture(nullptr),
		m_pSampleState(nullptr)
	{};
};

struct SShaderParam
{
	string m_strName;
	string m_strBuffer;
	uint32 m_nElemCnt;
	uint32 m_nRegPerElem;
	EShaderDataType m_eDataType;
};

struct SShaderActiveParam: public SShaderParam
{
	uint32 m_nVertexRegisterIndex;
	uint32 m_nVertexRegisterCnt;
	uint32 m_nPixelRegisterIndex;
	uint32 m_nPixelRegisterCnt;
	SShaderActiveParam():
		m_nVertexRegisterIndex(INVALID_32BIT),
		m_nVertexRegisterCnt(0),
		m_nPixelRegisterIndex(INVALID_32BIT),
		m_nPixelRegisterCnt(0)
	{}
};

class CShader: public CGraphicRes
{
public:
	CShader(CGraphic* pGraphic);

	~CShader();

	virtual bool CreateShaderFromFile(const char* szFileName) { return false; };

	void SetParamData(uint8 nIndex, const void* data, size_t size, EShaderDataType eDataType);

	void SetParamData(const char* szParamName, const void* data, size_t size, EShaderDataType eDataType);

	uint8 GetParamIndex(const char* szParamName);

	void SetShaderParam(const SMaterial& sMaterial, const SRenderEnvir& sEnvir, const CMatrix* arrMatrix, uint8 nMatrixCnt);

	const vector<SShaderActiveParam*>& GetVectorParams() { return m_vecVectorParams; }

	const vector<SShaderActiveParam*>& GetSampleParams() { return m_vecSampleParams; }

protected:
	template<class dataType>
	void SetParamVector4(SShaderActiveParam& sParam, const TVector4<dataType>* data, uint32 nElemCnt);
	
	void SetParamMatrix(SShaderActiveParam& sParam, const CMatrix* pMatrix, uint32 nElemCnt);

	void SetParamTexture(SShaderActiveParam& sParam, CTexture* pTexture, SSampleState* pState = nullptr);
	
	void AddParam(bool bVertexShader, const char* strName, uint32 nRegisterIndex, uint32 nRegisterCnt, EShaderDataType eDataType, const void* pDefaultValue, 
		uint32 nCntPerReg, uint32 nRegPerElem, uint32 nElemCnt );

	void ApplyParam();

	vector<SShaderActiveParam*> m_vecShaderParams;
	vector<SShaderActiveParam*> m_vecVectorParams;
	vector<SShaderActiveParam*> m_vecSampleParams;
};

template<>
inline void CShader::SetParamVector4<float>( SShaderActiveParam& sParam, const TVector4<float>* data, uint32 nElemCnt )
{
	nElemCnt = min(nElemCnt, sParam.m_nElemCnt);
	memcpy(&sParam.m_strBuffer[0], data, sizeof(TVector4<float>) * nElemCnt);
}

template<class dataType>
inline void CShader::SetParamVector4( SShaderActiveParam& sParam, const TVector4<dataType>* data, uint32 nElemCnt )
{
	nElemCnt = min(nElemCnt, sParam.m_nElemCnt);
	CVector4f* pDes = (CVector4f* )&sParam.m_strBuffer[0];
	for (uint32 i = 0; i < nElemCnt; i ++)
		pDes[i] = (CVector4f)data[i];
}

