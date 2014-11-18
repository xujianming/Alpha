#pragma once

#include <d3dx9.h>
#include "AlphaCommon\AlphaCommonType.h"

class CTexture;
class CGraphic;
struct SVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
	D3DXVECTOR3 normal;
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};
class CModel
{
private:
	
public:
	CModel(CGraphic* pGraphic);
	~CModel();

	bool Initialize(char* szModelFile, char* szTextureFile);
	void Shutdown();

	
	CTexture* GetTexture();
	const  SVertexType* GetVertexBuffer();
	uint16 GetVertexType();
	uint16 GetVertexCount();
	uint16* GetIndexBuffer();
	uint16 GetIndexCount();
private:
	bool InitializeBuffers(IDirect3DDevice9* pDevice);
	void ShutdownBuffers();
	void RenderBuffers(IDirect3DDevice9* pDevice);

	bool LoadTexture(IDirect3DDevice9* pDevice, char* szTextureFile);
	void ReleaseTexture();

	bool LoadModel(char* szModelFile);
	void ReleaseModel();

private:
	SVertexType* m_vertexBuffer;
	uint16* m_indexBuffer;
	uint16 m_vertexCount, m_indexCount;
	CTexture* m_Texture;
	ModelType* m_model;
	CGraphic* m_pGraphic;
};