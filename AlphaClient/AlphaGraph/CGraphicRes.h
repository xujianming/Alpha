#pragma once

#include "AlphaCommon\TInvasiveList.h"
#include "AlphaCommon\AlphaCommonType.h"
#include "AlphaCommon\IAlphaUnknown.h"

class CGraphic;
class CGraphicResMgr;

enum EResourceType
{
	ERT_VertexBuffer,
	ERT_IndexBuffer,
	ERT_Texture,
	ERT_Shader,
	ERT_RenderTarget,
	ERT_Invalid,
};

class CGraphicRes: public TInvasiveNode<CGraphicRes>,
					public IAlphaUnknown
{
public:
	CGraphicRes(CGraphic* pGraphic);
	virtual ~CGraphicRes();

	CGraphicResMgr* GetResMgr();

	void SetVedioMemSize(uint32 nMemSize);

	void AddVedioMemSize(uint32 nMemSize);

	EResourceType GetResType();

	uint32 GetUseFrame();

	void Use();

	void OnRestore();

	void OnLostDevice();

	void OnFreeMemory();

private:
	uint32 m_nVedioMemSize;
	uint32 m_nUseFrame;
	EResourceType m_eResType;
	CGraphic* m_pGraph;
};