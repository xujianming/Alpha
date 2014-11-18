#pragma once

#include "GraphicHelp.h"
#include "memory.h"
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
	bool m_bZWR;			//深度值写入	

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