#pragma once

#include "CAlphaCommonType.h"

struct SWindowContext
{
	void* m_pContext;
	void* m_pHandle;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static VOID CALLBACK TimeProp(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
};


class CAlphaWindow
{
public:
	CAlphaWindow();
	~CAlphaWindow();

	void* GetHandle();

	void Initialize(void* pContext, uint16 width, uint16 height, char *szTitle, uint16 iconID);
	virtual void Destroy();

	virtual void OnCreated();
private:
	SWindowContext m_Context;
};