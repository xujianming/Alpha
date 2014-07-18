////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
#include "stdafx.h"
#include "CTexture.h"
#include <d3dx9.h>

CTexture::CTexture()
{
	m_texture = 0;
}


CTexture::CTexture(const CTexture& other)
{
}


CTexture::~CTexture()
{
}


bool CTexture::Initialize(IDirect3DDevice9* pDevice, char* filename)
{
	HRESULT result;

	// Load the texture in.
	result = D3DXCreateTextureFromFile(pDevice, filename, &m_texture);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void CTexture::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


IDirect3DTexture9* CTexture::GetTexture()
{
	return m_texture;
}