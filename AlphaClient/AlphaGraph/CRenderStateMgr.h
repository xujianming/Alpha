#pragma once

class CProgram;
class CGraphic;

class CRenderStateMgr
{
public:
	CRenderStateMgr(CGraphic* pGraphic);
	
	virtual ~CRenderStateMgr();

	void SetProgram(CProgram* pProgram);

	void SetAlphaBlend();

	void SetZTest(bool bTest);

	void SetFillModel();

	void SetRenderTargetParam();

	void SetStencilParam();

	void SetScissorRect();

	void ApplyMaterialParam();

	void ApplyRenderTargetParam();

	void Reset();

protected:
	CGraphic* m_pGraphic;
};