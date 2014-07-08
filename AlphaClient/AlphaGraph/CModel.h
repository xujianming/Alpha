#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CTexture;

class CModel
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
public:
	CModel();
	~CModel();

	bool Initialize(IDirect3DDevice9* pDevice, char* szModelFile, char* szTextureFile);
	void Shutdown();
	void Render(IDirect3DDevice9*);

	int GetIndexCount();
	IDirect3DTexture9* GetTexture();
private:
	bool InitializeBuffers(IDirect3DDevice9* pDevice);
	void ShutdownBuffers();
	void RenderBuffers(IDirect3DDevice9* pDevice);

	bool LoadTexture(IDirect3DDevice9* pDevice, char* szTextureFile);
	void ReleaseTexture();

	bool LoadModel(char* szModelFile);
	void ReleaseModel();

private:
	IDirect3DVertexBuffer9 *m_vertexBuffer;
	IDirect3DIndexBuffer9* m_indexBuffer;
	int m_vertexCount, m_indexCount;
	CTexture* m_Texture;
	ModelType* m_model;
};