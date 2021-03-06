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
	CGraphicRes(CGraphic* pGraphic, EResourceType eResType);
	virtual ~CGraphicRes();

	CGraphicResMgr* GetResMgr();

	void SetVedioMemSize(uint32 nMemSize);

	void AddVedioMemSize(int32 nMemSize);

	EResourceType GetResType();

	uint32 GetUseFrame();

	virtual void Use();

	virtual void OnRestore();

	virtual void OnLostDevice();

	virtual void OnFreeMemory();

	void AddRef();

	void Release();

	uint32 GetRef();

protected:
	uint32 m_nVedioMemSize;
	uint32 m_nUseFrame;
	EResourceType m_eResType;
	CGraphic* m_pGraphic;
	uint32 m_nRef;
};