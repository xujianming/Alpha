#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CAlphaWindow;
class CGraphicD3D9;
class CScene;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void Initialize(CAlphaWindow* pWnd);
	void EnterOneFrame();
	void SetMainScene(CScene *pScene);

private:
	CAlphaWindow* m_pWnd;
	CGraphicD3D9* m_pGraphic;
	CScene* m_pMainScene;
};