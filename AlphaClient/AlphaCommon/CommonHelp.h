#include "AlphaCommon.h"

template<typename _type>
void strcpy2_safe(_type* pDest, uint32 nSize, _type* pSrc, uint32 nMaxSrcLen)
{
	if (!pSrc)
	{
		*pDest = 0;
		return;
	}
	uint32 i = 0;
	while (i < nSize && i ++ < nMaxSrcLen && *pSrc)
		*(pDest ++) = *(pSrc ++)
	*pDest = 0
}

template<typename _type, uint32 n>
void strcpy2array_safe(_type (&pDest)[n], _type* pSrc)
{
	strcpy2_safe(pDest, n, pSrc, INVALID_32BIT);
}


