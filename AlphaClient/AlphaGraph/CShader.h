#pragma once

#include <string>
#include <vector>
#include "AlphaCommon\TVector.h"
#include "CGraphicRes.h"
#include "GraphicHelp.h"
#include "AlphaCommon\AlphaCommonType.h"
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

struct SShaderTextureState: public SSampleState
{
	CTexture* m_pTexture;
};

struct SShaderParam
{
	string m_strName;
	string m_strBuffer;
	uint8 m_nElemCnt;
	uint8 m_nRegPerElem;
	EShaderDataType m_eDataType;
};

struct SShaderActiveParam
{
	SShaderParam* m_pParam;
	uint32 m_nVertexRegisterIndex;
	uint32 m_nVertexRegisterCnt;
	uint32 m_nPixelRegisterIndex;
	uint32 m_nPixelRegisterCnt;
	SShaderActiveParam():
		m_pParam(NULL),
		m_nVertexRegisterIndex(INVALID_32BIT),
		m_nVertexRegisterCnt(0),
		m_nPixelRegisterIndex(INVALID_32BIT),
		m_nPixelRegisterCnt(0)
	{}
};

class CProgram
{

};

class CShader: public CGraphicRes
{
public:
	CShader(CGraphic* pGraphic);

	~CShader();

	virtual bool CreateShaderFromFile(const char* szFileName) { return false; };

	void SetParamData(const char* szName, const void* data, size_t size, EShaderDataType eDataType);

protected:
	template<class dataType>
	void SetParamVector4(SShaderParam* pParam, TVector4<dataType> data, size_t size, EShaderDataType eDataType);
	
	void SetParamMatrix(SShaderParam* pParam, matrix4x4f matrix);

	void SetParamTexture(SShaderParam* pParam, CTexture* texture);
	
	void AddParam(bool bVertexShader, const char* strName, uint32 nRegisterIndex, uint32 nRegisterCnt, EShaderDataType eDataType, const void* pDefaultValue, 
		uint32 nCntPerReg, uint32 nRegPerElem, uint32 nElemCnt );

	vector<SShaderActiveParam> m_vecShaderParams;
};

template<class dataType>
void CShader::SetParamVector4( SShaderParam* pParam, TVector4<dataType> data, size_t size, EShaderDataType eDataType )
{

}
