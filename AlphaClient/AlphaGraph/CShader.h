#pragma once

#include <string>
#include <vector>
#include "AlphaCommon\TVector.h"
#include "CGraphicRes.h"

class CTexture;

enum EShaderDataType
{
	eSDT_4Bool,
	eSDT_4Int32,
	eSDT_4Uint32,
	eSDT_4Float,
	eSDT_4Matrix,
	eSDT_Cnt,
};

struct SShaderTextureState: public SSampleState
{
	CTexture* m_pTexture;
};

struct SShaderParam
{
	std::string m_strName;
	std::string m_strSemantic;
	std::string m_strBuffer;
	uint8 m_nElemCnt;
	EShaderDataType m_eDataType;
};

class CProgram
{

};

class CShader: public CGraphicRes
{
public:
	CShader(CGraphic* pGraphic);
	~CShader();

	

protected:
	template<class dataType>
	void SetParam(uint8 nParamIndex, TVector4<dataType> data, size_t size, EShaderDataType eDataType);
	std::vector<SShaderParam> m_vecShaderParams;
};