#pragma once

#include "CAlphaCommonType.h"

class CAlphaWindow
{
public:
	CAlphaWindow();
	~CAlphaWindow();

	bool Initialize(void* hInstance, uint16 width, uint16 height, char *szTitle, uint16 iconID);
	virtual void Destroy();
};