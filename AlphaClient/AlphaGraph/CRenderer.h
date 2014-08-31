#pragma once

#include <d3d9.h>

class CAlphaWindow;
class CGraphic;
class CScene;
class CModel;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void Initialize(CAlphaWindow* pWnd);
	void EnterOneFrame();
	void SetMainScene(CScene *pScene);

	CGraphic* GetGraphic(){ return m_pGraphic; }

private:
	CAlphaWindow* m_pWnd;
	CGraphic* m_pGraphic;
	CScene* m_pMainScene;

	CModel* m_pModel;
};