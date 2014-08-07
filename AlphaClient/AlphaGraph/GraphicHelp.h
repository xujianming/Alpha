#pragma once

#include "AlphaCommon\AlphaCommonType.h"

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

	D3DFMT_UNKNOWN              =  0,

	D3DFMT_R8G8B8               = 20,
	D3DFMT_A8R8G8B8             = 21,
	D3DFMT_X8R8G8B8             = 22,
	D3DFMT_R5G6B5               = 23,
	D3DFMT_X1R5G5B5             = 24,
	D3DFMT_A1R5G5B5             = 25,
	D3DFMT_A4R4G4B4             = 26,
	D3DFMT_R3G3B2               = 27,
	D3DFMT_A8                   = 28,
	D3DFMT_A8R3G3B2             = 29,
	D3DFMT_X4R4G4B4             = 30,
	D3DFMT_A2B10G10R10          = 31,
	D3DFMT_A8B8G8R8             = 32,
	D3DFMT_X8B8G8R8             = 33,
	D3DFMT_G16R16               = 34,
	D3DFMT_A2R10G10B10          = 35,
	D3DFMT_A16B16G16R16         = 36,

	D3DFMT_A8P8                 = 40,
	D3DFMT_P8                   = 41,

	D3DFMT_L8                   = 50,
	D3DFMT_A8L8                 = 51,
	D3DFMT_A4L4                 = 52,

	D3DFMT_V8U8                 = 60,
	D3DFMT_L6V5U5               = 61,
	D3DFMT_X8L8V8U8             = 62,
	D3DFMT_Q8W8V8U8             = 63,
	D3DFMT_V16U16               = 64,
	D3DFMT_A2W10V10U10          = 67,

	D3DFMT_UYVY                 = MAKEFOURCC('U', 'Y', 'V', 'Y'),
	D3DFMT_R8G8_B8G8            = MAKEFOURCC('R', 'G', 'B', 'G'),
	D3DFMT_YUY2                 = MAKEFOURCC('Y', 'U', 'Y', '2'),
	D3DFMT_G8R8_G8B8            = MAKEFOURCC('G', 'R', 'G', 'B'),

	D3DFMT_D16_LOCKABLE         = 70,
	D3DFMT_D32                  = 71,
	D3DFMT_D15S1                = 73,
	D3DFMT_D24S8                = 75,
	D3DFMT_D24X8                = 77,
	D3DFMT_D24X4S4              = 79,
	D3DFMT_D16                  = 80,

	D3DFMT_D32F_LOCKABLE        = 82,
	D3DFMT_D24FS8               = 83,


	D3DFMT_L16                  = 81,

	D3DFMT_VERTEXDATA           =100,
	D3DFMT_INDEX16              =101,
	D3DFMT_INDEX32              =102,

	D3DFMT_Q16W16V16U16         =110,

	D3DFMT_MULTI2_ARGB8         = MAKEFOURCC('M','E','T','1'),

	// Floating point surface formats

	// s10e5 formats (16-bits per channel)
	D3DFMT_R16F                 = 111,
	D3DFMT_G16R16F              = 112,
	D3DFMT_A16B16G16R16F        = 113,

	// IEEE s23e8 formats (32-bits per channel)
	D3DFMT_R32F                 = 114,
	D3DFMT_G32R32F              = 115,
	D3DFMT_A32B32G32R32F        = 116,

	D3DFMT_CxV8U8               = 117,



	D3DFMT_FORCE_DWORD          =0x7fffffff
};