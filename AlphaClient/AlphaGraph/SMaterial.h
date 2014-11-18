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
		m_nSrcBlend(eMBT_Disable),
		m_nDestBlend(eMBT_Disable), 
		m_nAlphaRef(0),
		m_nZTestFun(eMCF_LessEqual),
		m_bZWR(true),
		m_nRGBWriteFlag(eMCWF_All),
		m_nCullType(eMCT_CCW)
	{
		memset(m_pTexture, 0, sizeof(m_pTexture));
	}
};