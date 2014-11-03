#pragma once

#include "GraphicHelp.h"
#include "memory.h"
class CTexture;
class CShader;

struct SMaterial
{
	CTexture* m_pTexture[MAX_TEXTURE_STAGE];
	CShader* m_pShader;
	//alphc���
	uint8 m_nSrcBlend;		//Դ��Ϸ�ʽ
	uint8 m_nDestBlend;		//Ŀ���Ϸ�ʽ
	//alpha����
	uint8 m_nAlphaRef;		//alpha���ԵĲο�ֵ
	//��Ȳ���
	uint8 m_nZTestFun;		//��Ȳ��Ժ���
	bool m_bZWR;			//���ֵд��	

	uint8 m_nRGBWriteFlag;
	uint8 m_nCullType;

	SMaterial() :
		m_pShader(nullptr),
		m_nSrcBlend(0),
		m_nDestBlend(0), 
		m_nAlphaRef(0),
		m_nZTestFun(0),
		m_bZWR(1),
		m_nRGBWriteFlag(0),
		m_nCullType(0)
	{
		memset(m_pTexture, 0, sizeof(m_pTexture));
	}
};