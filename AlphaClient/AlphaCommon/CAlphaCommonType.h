#pragma once

#include "TMatrix.h"
#include "TVector.h"

#define SAFE_DELETE(p) {if (p) delete (p); (p) = NULL;}
#define SAFE_RELEASE(p) {if (p) (p)->Release(); (p) = NULL;}

#ifdef _WIN32
	
typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

typedef unsigned char tByte;

const uint8  INVALID_8BIT  = uint8(-1); 
const uint16 INVALID_16BIT = uint16(-1);
const uint32 INVALID_32BIT = uint32(-1);
const uint64 INVALID_64BIT = uint64(-1);

#define vector2f TVector2<float>
#define vector3f TVector3<float>
#define vector4f TVector4<float>

#define matrix3x3f TMatrix3<float>
#define matrix4x4f TMatrix4<float>

#endif