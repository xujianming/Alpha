#pragma once

#include "GraphicHelp.h"

class CTexture;
class Shader;

struct SMaterial
{
	CTexture* pTexture[MAX_TEXTURE_STAGE];
	CShader* pShader;
	//alphc混合
	uint8 nSrcBlend;		//源混合方式
	uint8 nDestBlend;		//目标混合方式
	//alpha测试

};