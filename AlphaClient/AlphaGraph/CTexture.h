#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d9.h>
#include <d3dx9.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class CTexture
{
public:
	CTexture();
	CTexture(const CTexture&);
	~CTexture();

	bool Initialize(IDirect3DDevice9* pDevice, char* wszFileName);
	void Shutdown();

	IDirect3DTexture9* GetTexture();

private:
	IDirect3DTexture9* m_texture;
};

