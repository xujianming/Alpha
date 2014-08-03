#pragma once

#include "AlphaCommonType.h"

class IAlphaUnknown
{
public:
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual uint32 GetRef() = 0;
};