#pragma once

#include "AlphaCommon\AlphaCommonType.h"

#define MAX_TEXTURE_STAGE 8

enum EPrimitiveType
{
	ePT_PointList,
	ePT_LineList,
	ePT_LineStrip,
	ePT_TriangleList,
	ePT_TriangleStrip,
	ePT_TriangleFan,
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

inline uint32 GetBitPerPixel(ETextureFormat eFormat)
{
	uint32 size[] = { 4, 8, 24, 32, 16, 16, 4, 8, 24, 32, 16, 16, 16, 8, 16, 16, 32, 32, 32, 32, 64, 64, 128, 0, 16, 32, 32 };
	return size[eFormat];
}

inline bool IsDepthFormat(ETextureFormat eFormat)
{
	return eFormat == eTF_D16 || eFormat == eTF_D24S8 || eFormat == eTF_INTZ;
}