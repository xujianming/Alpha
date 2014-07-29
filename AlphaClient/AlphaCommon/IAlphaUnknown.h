#pragma once

class IAlphaUnknown
{
public:
	virtual void AddRef() = 0;
	virtual void Release() = 0;
};