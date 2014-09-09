#pragma once

#include "GraphicHelp.h"

class CTexture;
class CShader;

struct SMaterial
{
	CTexture* m_pTexture[MAX_TEXTURE_STAGE];
	CShader* m_pShader;
	//alphc混合
	uint8 m_nSrcBlend;		//源混合方式
	uint8 m_nDestBlend;		//目标混合方式
	//alpha测试
	uint8 m_nAlphaRef;		//alpha测试的参考值
	//深度测试
	uint8 m_nZTestFun;		//深度测试函数
	uint8 m_nZWR;			//深度值写入	


};