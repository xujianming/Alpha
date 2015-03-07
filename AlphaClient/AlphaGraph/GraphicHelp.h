#pragma once

#include "AlphaCommon\AlphaCommonType.h"

#define MAX_TEXTURE_STAGE 8

#define MAX_RENDER_TARGET 4

enum EPrimitiveType
{
	ePT_PointList,
	ePT_LineList,
	ePT_LineStrip,
	ePT_TriangleList,
	ePT_TriangleStrip,
	ePT_TriangleFan,
	ePT_Cnt
};	

struct SVertexElem
{
	uint16 offset;	//在顶点结构中的偏移
	uint8 type;		//类型
	uint8 usage;	//semantic
};

enum EDeclareType
{
	eDT_1Float,
	eDT_2Float,
	eDT_3Float,
	eDT_4Float,
	eDT_4uint8N,
	eDT_4uint8,
	eDT_Cnt,
};

enum EDeclareUsage
{
	eDU_Position,
	eDU_Color0,
	eDU_Color1,
	eDU_Normal,
	eDU_Texcoord0,
	eDU_Texcoord1,
	eDU_Texcoord2,
	eDU_Texcoord3,
	eDU_Texcoord4,
	eDU_Texcoord5,
	eDU_Texcoord6,
	eDU_Texcoord7,
	eDU_Cnt,
};

enum ETextureFormat
{
	eTF_DXT1 = 0,
	eTF_DXT5 = 1,
	eTF_RBG24 = 2,
	eTF_ARGB32 = 3,
	eTF_R5G6B5 = 4,
	eTF_A4R4G4B4 = 5,
	eTF_ETC2 = 6,
	eTF_EAC = 7,
	eTF_BGR24 = 8,
	eTF_ABGR32 = 9,
	eTF_B5G6R5 = 10,
	eTF_A4B4G4R4 = 11,
	eTF_R4G4B4A4 = 12,
	eTF_A8 = 13,
	eTF_SR8G8 = 14,
	eTF_F16 = 15,
	eTF_F32 = 16,
	eTF_A2R10G10B10 = 17,
	eTF_G16R16 = 18,
	eTF_G16R16F = 19,
	eTF_ARGB64F = 20,
	eTF_G32R32F = 21,
	eTF_ABGR128F = 22,
	eTF_NULLRT = 23,
	eTF_D16 = 24,
	eTF_D24S8 = 25,
	eTF_INTZ = 26,
	eTF_Cnt = 27,
	eTF_UNKNOWN = 28,
};

enum ETextureAddress
{
	eTA_Wrap,
	eTA_Border,
	eTA_Clamp,
	eTA_Mirror,
	eTA_Cnt
};

enum ETextureFilter
{
	eTFL_Point,
	eTFL_Liner,
	eTFL_None,
	eTFL_Cnt
};

enum ESampleState
{
	eSS_MipFilter,
	eSS_MinFilter,
	eSS_MagFilter,
	eSS_AddressU,
	eSS_AddressV,
	eSS_AddressW,
	eSS_BordeColor,
	eSS_MipmapLodBias,
	eSS_Cnt
};

enum EMaterialCullType
{
	eMCT_None = 1,
	eMCT_CW = 2, 
	eMCT_CCW = 3,
};

enum EMaterialCmpFunc
{
	eMCF_Disable,
	eMCF_Never,
	eMCF_Less,
	eMCF_Equal,
	eMCF_LessEqual,
	eMCF_Greater,
	eMCF_NotEqual,
	eMCF_GreaterEqual,
	eMCF_Always,
};

enum EMaterialBleadType
{
	eMBT_Disable,
	eMBT_Zero,
	eMBT_One,
	eMBT_SrcColor,
	eMBT_InvSrcColor,
	eMBT_SrcAlpha,
	eMBT_InvSrcAlpha,
	eMBT_DesAlpha,
	eMBT_InvDesAlpha,
	eMBT_DesColor,
	eMBT_InvDesColor,
};

enum EMaterialColorWriteFlag
{
	eMCWF_None = 0,
	eMCWF_Red = 1,
	eMCWF_Green = 1 << 1,
	eMCWF_Blue = 1 << 2,
	eMCWF_Alpha = 1 << 3,
	eMCWF_All = 0xf,
};

struct SSampleState
{
	uint32 m_eSampleState[eSS_Cnt];
	SSampleState()
	{
		m_eSampleState[eSS_MipFilter] = eTFL_Liner;
		m_eSampleState[eSS_MinFilter] = eTFL_Liner;
		m_eSampleState[eSS_MagFilter] = eTFL_Liner;
		m_eSampleState[eSS_AddressU] = eTA_Wrap;
		m_eSampleState[eSS_AddressV] = eTA_Wrap;
		m_eSampleState[eSS_AddressW] = eTA_Wrap;
		m_eSampleState[eSS_BordeColor] = 0;
		m_eSampleState[eSS_MipmapLodBias] = 0;
	}
};

inline uint32 GetBitPerPixel(ETextureFormat eFormat)
{
	uint32 size[] = { 4, 8, 24, 32, 16, 16, 4, 8, 24, 32, 16, 16, 16, 8, 16, 16, 32, 32, 32, 32, 64, 64, 128, 0, 16, 32, 32 };
	return size[eFormat];
}

inline bool IsDepthFormat(ETextureFormat eFormat)
{
	return eFormat == eTF_D16 || eFormat == eTF_D24S8 || eFormat == eTF_INTZ;
}

inline bool IsStencilFormat(ETextureFormat eFormat)
{
	return eFormat == eTF_D24S8 || eFormat == eTF_INTZ;
}

struct SLight
{
	enum ELightType
	{
		eLT_Direct,
		eLT_Point,
		eLT_Spot,
		eLT_Cnt
	};
	ELightType m_eType;
	CVector3f m_vPos;
	CVector3f m_vDir;
	float m_fAngle;
	uint32 m_nColor;
	float m_fRange;
	float m_fAtten0;
	float m_fAtten1;
	float m_fAtten2;
	SLight()
	{
		SetDirectLigth(CVector3f(0.717f, -0.717f, 0.0f), 0xffffffff);
	}
	void SetDirectLigth(const CVector3f& vDir, uint32 nColor = 0xffffffff)
	{
		m_eType = eLT_Direct;
		m_vDir = vDir;
		m_nColor = nColor;
		m_fRange = 100000;
		m_fAtten0 = 1;
		m_fAtten1 = 0;
		m_fAtten2 = 0;
		m_vDir.normalize();
	}
	void SetPointLight(const CVector3f& vPos, 
						float fRange,
						uint32 nColor = 0xffffffff,
						float fConstant = 0.0,
						float fLinear = 1.0,
						float fQuadric = 0.0)
	{
		m_eType = eLT_Point;
		m_fRange = fRange;
		m_nColor = nColor;
		m_fAtten0 = fConstant;
		m_fAtten1 = fLinear;
		m_fAtten2 = fQuadric;
	}
	void SetSpotLight(const CVector3f& vPos,
						const CVector3f& vDir,
						float fAngle,
						float fRange,
						uint32 nColor = 0xffffffff,
						float fConstant = 0.0,
						float fLinear = 1.0,
						float fQuadric = 0.0)
	{
		m_eType = eLT_Spot;
		m_vPos = vPos;
		m_vDir = vDir;
		m_fAngle = fAngle;
		m_fRange = fRange;
		m_nColor = nColor;
		m_fAtten0 = fConstant;
		m_fAtten1 = fLinear;
		m_fAtten2 = fQuadric;
	}

};