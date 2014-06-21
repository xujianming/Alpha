#include "stdafx.h"
#include <windows.h>
#include "CAlphaWindow.h"

struct SWindowContext
{
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};



bool CAlphaWindow::Initialize( void* hInstance, uint16 width, uint16 height, char *szTitle, uint16 iconID) )
{
	WNDCLASSEX wndclsex;
	wndclsex.cbSize = sizeof(WNDCLASSEX);
	wndclsex.cbClsExtra = 0;
	wndclsex.cbWndExtra = 0;
	wndclsex.hbrBackground = NULL;
	wndclsex.hIcon = NULL;
	wndclsex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclsex.hInstance = HINSTANCE(hInstance);
	wndclsex.lpfnWndProc = SWindowContext::WndProc;
	wndclsex.lpszClassName = "CAlphaWindow";
	wndclsex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclsex.lpszMenuName = NULL;
	wndclsex.hIconSm = LoadIcon(wndclsex.hInstance, MAKEINTRESOURCE(iconID));

	RegisterClassEx(&wndclsex);

	HWND hWnd;
	hWnd = CreateWindowEx("CAlphaWindow", szTitle, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, wndclsex.hInstance, this);
}
