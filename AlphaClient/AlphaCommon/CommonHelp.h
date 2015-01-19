#include "AlphaCommon.h"

template<typename _type>
void strcpy2_safe(_type* pDest, _type* pSrc, uint32 nSize, uint32 nMaxSrcLen)
{

}

template<typename _type, uint32 n>
void strcpy2array_safe(_type (&pDest)[n], _type* pSrc)
{
	strcpy2_safe(pDest, pSrc, n, INVALID_32BIT);
}


