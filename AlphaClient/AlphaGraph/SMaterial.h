#pragma once

#include "GraphicHelp.h"

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
	uint8 m_nZWR;			//���ֵд��	


};