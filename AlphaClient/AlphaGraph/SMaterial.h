#pragma once

#include "GraphicHelp.h"

class CTexture;
class Shader;

struct SMaterial
{
	CTexture* pTexture[MAX_TEXTURE_STAGE];
	CShader* pShader;
	//alphc���
	uint8 nSrcBlend;		//Դ��Ϸ�ʽ
	uint8 nDestBlend;		//Ŀ���Ϸ�ʽ
	//alpha����

};