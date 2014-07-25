#pragma once

class IAlphaUnknown
{
protected:
	virtual void AddRef() = 0;
	virtual void DeRef() = 0;
};