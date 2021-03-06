#include "stdafx.h"
#include "CModel.h"
#include "CTexture.h"
#include "AlphaCommon\AlphaCommonType.h"
#include <fstream>
#include "CShader.h"
#include "CGraphicD3D9.h"
#include "CTextureD3D9.h"
using namespace std;

CModel::CModel(CGraphic *pGraphic):
	m_pGraphic(pGraphic)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
}


CModel::~CModel()
{
}


bool CModel::Initialize(char* modelFilename, char* textureFilename)
{
	CGraphicD3D9* pGraphicD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	bool result;
	// Load in the model data.
	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffer that hold the geometry for the model.
	result = InitializeBuffers(pGraphicD3D9->GetDevice());
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(pGraphicD3D9->GetDevice(), textureFilename);
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

uint16 CModel::GetIndexCount()
{
	return m_indexCount;
}


CTexture* CModel::GetTexture()
{
	return m_Texture;
}


bool CModel::InitializeBuffers(IDirect3DDevice9* device)
{
	m_vertexBuffer = new SVertexType[m_vertexCount];
	m_indexBuffer = new uint16[m_indexCount];

	for(uint16 i=0; i< m_vertexCount; i++)
	{
		m_vertexBuffer[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		m_vertexBuffer[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		m_vertexBuffer[i].normal =  D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		m_indexBuffer[i] = i;
	}

	return true;
}


void CModel::ShutdownBuffers()
{
	delete[] m_vertexBuffer;
	delete[] m_indexBuffer;
	return;
}

bool CModel::LoadTexture(IDirect3DDevice9* device, char* filename)
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	// Create the texture object.
	m_Texture = pGraphic->CreateTextureFromFile(filename);
	if(!m_Texture)
	{
		return false;
	}
	return true;
}


void CModel::ReleaseTexture()
{
	SAFE_RELEASE(m_Texture);
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

const SVertexType* CModel::GetVertexBuffer()
{
	return m_vertexBuffer;
}

uint16 CModel::GetVertexType()
{
	SVertexElem arrElem[] = 
	{
		0, eDT_3Float, eDU_Position,
		12, eDT_2Float, eDU_Texcoord0,
		20, eDT_3Float, eDU_Normal
	};
	uint16 nVertexFormat = m_pGraphic->CreateVertexFormat(arrElem, ELEMENT_CNT(arrElem));
	return nVertexFormat;
}

uint16 CModel::GetVertexSize()
{
	return sizeof(SVertexType);
}

uint16 CModel::GetVertexCount()
{
	return m_vertexCount;
}

uint16* CModel::GetIndexBuffer()
{
	return m_indexBuffer;
}
