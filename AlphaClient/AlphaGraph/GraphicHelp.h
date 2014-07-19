#pragma once

#include "AlphaCommon\CAlphaCommonType.h"

enum EPrimitiveType
{
	EPT_PointList,
	EPT_LineList,
	EPT_LineStrip,
	EPT_TriangleList,
	EPT_TriangleStrip,
	EPT_TriangleFan,
};	

struct SVertexElem
{
	uint16 offset;	//在顶点结构中的偏移
	uint8 type;		//类型
	uint8 usage;	//semantic
};

enum EDeclareType
{
	EDT_Float,
	EDT_Float2,
	EDT_Float3,
	EDT_Float4,
	EDT_Cnt,
};

enum EDeclareUsage
{
	EDU_Position,
	EDU_Color0,
	EDU_Color1,
	EDU_Normal,
	EDU_Texcoord0,
	EDU_Texcoord1,
	EDU_Texcoord2,
	EDU_Texcoord3,
	EDU_Texcoord4,
	EDU_Texcoord5,
	EDU_Texcoord6,
	EDU_Texcoord7,
	EDU_Cnt,
};