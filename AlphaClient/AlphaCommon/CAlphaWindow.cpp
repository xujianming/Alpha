#include "stdafx.h"
#include <windows.h>
#include "CAlphaWindow.h"

LRESULT CALLBACK SWindowContext::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

VOID CALLBACK SWindowContext::TimeProp(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{

}


CAlphaWindow::CAlphaWindow()
{
	
}


CAlphaWindow::~CAlphaWindow()
{

}


void CAlphaWindow::Initialize( void* pContext, uint16 width, uint16 height, char *szTitle, uint16 iconID)
{
	WNDCLASSEX wndclsex;
	wndclsex.cbSize = sizeof(WNDCLASSEX);
	wndclsex.cbClsExtra = 0;
	wndclsex.cbWndExtra = 0;
	wndclsex.hbrBackground = NULL;
	wndclsex.hIcon = NULL;
	wndclsex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclsex.hInstance = HINSTANCE(pContext);
	wndclsex.lpfnWndProc = SWindowContext::WndProc;
	wndclsex.lpszClassName = "CAlphaWindow";
	wndclsex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclsex.lpszMenuName = NULL;
	wndclsex.hIconSm = LoadIcon(wndclsex.hInstance, MAKEINTRESOURCE(iconID));

	RegisterClassEx(&wndclsex);

	HWND hWnd;
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, "CAlphaWindow", szTitle, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, wndclsex.hInstance, this);

	m_Context.m_pContext = wndclsex.hInstance;
	m_Context.m_pHandle = hWnd;

	int32 cx = GetSystemMetrics(SM_CXSCREEN);
	int32 cy = GetSystemMetrics(SM_CYSCREEN);

	int32 posX = (cx - width) / 2;
	int32 posY = (cy - height) / 2;

	MoveWindow(GetHandle(), posX, posY, width, height, false);

	ShowWindow(GetHandle(), SW_SHOW);

	UpdateWindow(GetHandle());

	SetTimer(GetHandle(), uint32(this), 50, m_Context.TimeProp);

	OnCreated();
}



HWND CAlphaWindow::GetHandle()
{
	return (HWND)m_Context.m_pHandle;
}

void CAlphaWindow::OnCreated()
{

}

void CAlphaWindow::Destroy()
{

}

RECT CAlphaWindow::GetClientRect()
{
	RECT rect;
	::GetClientRect(GetHandle(), &rect);
	return rect;
}
