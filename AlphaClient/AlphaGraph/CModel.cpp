#include "stdafx.h"
#include "CModel.h"
#include "CTexture.h"
#include "AlphaCommon\CAlphaCommonType.h"
#include <iostream>
CModel::CModel()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
}


CModel::CModel(const CModel& other)
{
}


CModel::~CModel()
{
}


bool CModel::Initialize(IDirect3DDevice9* device, char* modelFilename, char* textureFilename)
{
	bool result;


	// Load in the model data.
	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the model.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}


void CModel::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Release the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void CModel::Render(IDirect3DDevice9* device)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(device);

	return;
}


int CModel::GetIndexCount()
{
	return m_indexCount;
}


IDirect3DTexture9* CModel::GetTexture()
{
	return m_Texture->GetTexture();
}


bool CModel::InitializeBuffers(IDirect3DDevice9* device)
{
	VertexType* vertices;
	uint16* indices;

	HRESULT result;

	// Now finally create the vertex buffer.
	result = device->CreateVertexBuffer(sizeof(VertexType) * m_vertexCount, 
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX0,
		D3DPOOL_MANAGED, &m_vertexBuffer, 0);
	if(FAILED(result))
		return false;


	// Create the index buffer.
	result = device->CreateIndexBuffer(m_indexCount * sizeof(uint16), 
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_indexBuffer, 0);
	if(FAILED(result))
		return false;


	m_vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	m_indexBuffer->Lock(0, 0, (void**)&indices, 0);
	// Load the vertex array and index array with data.
	for(uint16 i=0; i< m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		indices[i] = i;
	}
	m_vertexBuffer->Unlock();
	m_indexBuffer->Unlock();


	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void CModel::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void CModel::RenderBuffers(IDirect3DDevice9* device)
{
	device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VertexType));
	device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX0);
	device->SetIndices(m_indexBuffer);
	return;
}


bool CModel::LoadTexture(IDirect3DDevice9* device, char* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new CTexture;
	if(!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


void CModel::ReleaseTexture()
{
	// Release the texture object.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}


bool CModel::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.  If it could not open the file then exit.
	fin.open(filename);
	if(fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for(i=0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}


void CModel::ReleaseModel()
{
	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}