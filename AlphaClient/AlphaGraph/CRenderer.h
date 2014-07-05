#pragma once

class CAlphaWindow;
class CGraphicD3D9;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void Initialize(CAlphaWindow* pWnd);
	void EnterOneFrame();

private:
	CAlphaWindow* m_pWnd;
	CGraphicD3D9* m_pGraphic;
};