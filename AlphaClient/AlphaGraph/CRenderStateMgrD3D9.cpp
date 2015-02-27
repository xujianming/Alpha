#include "stdafx.h"
#include "CRenderStateMgrD3D9.h"
#include "CGraphicD3D9.h"
#include "CGeometryBufferD3D9.h"
#include "CVertexFormatD3D9.h"
#include "CShaderD3D9.h"
#include "CTextureD3D9.h"

D3DPRIMITIVETYPE g_PrimitiyType[ePT_Cnt] = 
{
	D3DPT_POINTLIST,
	D3DPT_LINELIST,
	D3DPT_LINESTRIP,
	D3DPT_TRIANGLELIST,
	D3DPT_TRIANGLESTRIP,
	D3DPT_TRIANGLEFAN,
};

CRenderStateMgrD3D9::CRenderStateMgrD3D9(CGraphic* pGraphic):
	CRenderStateMgr(pGraphic)
{

}

CRenderStateMgrD3D9::~CRenderStateMgrD3D9()
{

}

void CRenderStateMgrD3D9::SetAlphaBlend( uint8 nSrcBlend, uint8 nDesBlend )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	if (nSrcBlend != eMBT_Disable && nDesBlend != eMBT_Disable)
	{
		pGraphic->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pGraphic->GetDevice()->SetRenderState(D3DRS_SRCBLEND, nSrcBlend);
		pGraphic->GetDevice()->SetRenderState(D3DRS_DESTBLEND, nDesBlend);
	}
	else
	{
		pGraphic->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}	
}

void CRenderStateMgrD3D9::SetZTest( uint8 nZTestFun, bool bZWR )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	if (nZTestFun == eMCF_Disable)
		pGraphic->GetDevice()->SetRenderState(D3DRS_ZENABLE, false);
	else
	{
		pGraphic->GetDevice()->SetRenderState(D3DRS_ZENABLE, true);
		pGraphic->GetDevice()->SetRenderState(D3DRS_ZFUNC, nZTestFun);
	}
	pGraphic->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, bZWR);
}

void CRenderStateMgrD3D9::SetFillModel( uint8 nRGBWriteFlag, uint8 nCullType )
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	pGraphic->GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, nRGBWriteFlag);
	pGraphic->GetDevice()->SetRenderState(D3DRS_FILLMODE, nCullType);
}

void CRenderStateMgrD3D9::SetRenderTargetParam(const SRenderTargetInfo& info)
{
	CGraphicD3D9* pGraphicD3D9 = static_cast<CGraphicD3D9*>(m_pGraphic);
	for (int8 i = MAX_RENDER_TARGET - 1; i >= 0; i --)
	{
		pGraphicD3D9->GetDevice()->SetRenderTarget(i, NULL);
	}
	if (info.pRenderTargets[0])
	{
		for (int8 i = 0; i < MAX_RENDER_TARGET; i ++)
		{
			if (!info.pRenderTargets[i])
				break;
			CRenderTargetD3D* pTarget = static_cast<CRenderTargetD3D*>(info.pRenderTargets[i]);
			pGraphicD3D9->GetDevice()->SetRenderTarget(i, pTarget->GetRenderTargetSuface());
		}
	}
	else
	{
		pGraphicD3D9->GetDevice()->SetRenderTarget(0, pGraphicD3D9->GetBackBuffer());
	}
	if (info.pDepthpRenderTarget)
	{
		CRenderTargetD3D* pDepth = static_cast<CRenderTargetD3D*>(info.pDepthpRenderTarget);
		pGraphicD3D9->GetDevice()->SetDepthStencilSurface(pDepth->GetDepthStencilSuface());
	}
	else
	{
		CRenderTargetD3D* pDepth = static_cast<CRenderTargetD3D*>(pGraphicD3D9->GetMainRenderTarget());
		pGraphicD3D9->GetDevice()->SetDepthStencilSurface(pDepth->GetDepthStencilSuface());
	}
}

void CRenderStateMgrD3D9::SetStencilParam()
{

}

void CRenderStateMgrD3D9::SetScissorRect()
{

}

void CRenderStateMgrD3D9::SetShader( CShader* pShader )
{
	CRenderStateMgr::SetShader(pShader);

	const vector<SShaderActiveParam*>& sampleParam = pShader->GetSampleParams();
	IDirect3DDevice9* pDevice = static_cast<CGraphicD3D9*>(m_pGraphic)->GetDevice();
	for (uint32 i = 0; i < sampleParam.size(); i ++)
	{
		if (!sampleParam[i]->m_nPixelRegisterCnt)
			continue;
		SShaderTextureState *pState = (SShaderTextureState*)&sampleParam[i]->m_strBuffer[0];
		CTexture* pTexture = pState->m_pTexture;
		if (pTexture)
		{
			IDirect3DBaseTexture9 *pTex = (static_cast<CTextureD3D9*>(pTexture))->GetD3DTexture();
			uint32 nIndex = sampleParam[i]->m_nPixelRegisterIndex;
			pDevice->SetTexture(nIndex, pTex);
			if (pState->m_pSampleState)
			{
				DWORD address[eTA_Cnt] = 
				{
					D3DTADDRESS_WRAP,
					D3DTADDRESS_BORDER,
					D3DTADDRESS_CLAMP,
					D3DTADDRESS_MIRROR
				};

				DWORD filter[eTFL_Cnt] = 
				{
					D3DTEXF_POINT,
					D3DTEXF_LINEAR,
					D3DTEXF_NONE
				};
				SSampleState* pSampleState = pState->m_pSampleState;
				pDevice->SetSamplerState(nIndex, D3DSAMP_ADDRESSU, address[pSampleState->m_eSampleState[eSS_AddressU]]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_ADDRESSV, address[pSampleState->m_eSampleState[eSS_AddressV]]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_ADDRESSW, address[pSampleState->m_eSampleState[eSS_AddressW]]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_MIPFILTER, filter[pSampleState->m_eSampleState[eSS_MipFilter]]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_MINFILTER, filter[pSampleState->m_eSampleState[eSS_MinFilter]]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_MAGFILTER, filter[pSampleState->m_eSampleState[eSS_MagFilter]]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_BORDERCOLOR, pSampleState->m_eSampleState[eSS_BordeColor]);
				pDevice->SetSamplerState(nIndex, D3DSAMP_MIPMAPLODBIAS, pSampleState->m_eSampleState[eSS_MipmapLodBias]);
			}
		}
	}
	if (m_nVertexRegisterCnt)
		pDevice->SetVertexShaderConstantF(0, m_vecVertexShaderParam[0].v, m_nVertexRegisterCnt);
	if (m_nPixelRegisterCnt)
		pDevice->SetPixelShaderConstantF(0, m_vecPixelShaderParam[0].v, m_nPixelRegisterCnt);

	CShaderD3D9* pShaderD3D9 = static_cast<CShaderD3D9*>(pShader);
	pDevice->SetVertexShader(pShaderD3D9->GetVertexShader());
	pDevice->SetPixelShader(pShaderD3D9->GetPixelShader());

}

void CRenderStateMgrD3D9::Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint16 nVertexFormat, uint16 nVertexStride, const void* pArrVertex, const void* pArrIndex)
{
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	CVertexFormatD3D9* pVertexVormat = static_cast<CVertexFormatD3D9*>(pGraphic->GetVertexFormatMgr().GetVertexFormat(nVertexFormat));
	pGraphic->GetDevice()->SetVertexDeclaration(pVertexVormat->GetVertexDeclaration());
	if (pArrIndex)
	{
		pGraphic->GetDevice()->DrawIndexedPrimitiveUP(g_PrimitiyType[ePrimitiveType], 0, nVertexCnt, nPrimitiveCnt, pArrIndex, D3DFMT_INDEX16, pArrVertex, nVertexStride);
	}
	else
	{
		pGraphic->GetDevice()->DrawPrimitiveUP(g_PrimitiyType[ePrimitiveType], nPrimitiveCnt, pArrVertex, nVertexStride);
	}
}

void CRenderStateMgrD3D9::Draw(EPrimitiveType ePrimitiveType, uint16 nVertexCnt, uint16 nPrimitiveCnt, uint16 nVertexFormat, CGeometryBuffer* pVertexBuf, CGeometryBuffer* pIndexBuf)
{
	CVertexBufferD3D9* pVertexBuffer = static_cast<CVertexBufferD3D9*>(pVertexBuf);
	CIndexBufferD3D9* pIndexBuffer = static_cast<CIndexBufferD3D9*>(pIndexBuf);
	CGraphicD3D9* pGraphic = static_cast<CGraphicD3D9*>(m_pGraphic);
	CVertexFormatD3D9* pVertexVormat = static_cast<CVertexFormatD3D9*>(pGraphic->GetVertexFormatMgr().GetVertexFormat(nVertexFormat));
	pGraphic->GetDevice()->SetVertexDeclaration(pVertexVormat->GetVertexDeclaration());
	pGraphic->GetDevice()->SetStreamSource(0, static_cast<IDirect3DVertexBuffer9*>(pVertexBuffer->GetD3DBuffer()), 0, pVertexBuffer->GetStride());
	if (pIndexBuffer)
	{
		pGraphic->GetDevice()->SetIndices(static_cast<IDirect3DIndexBuffer9*>(pIndexBuffer->GetD3DBuffer()));
		pGraphic->GetDevice()->DrawIndexedPrimitive(g_PrimitiyType[ePrimitiveType], 0, 0, nVertexCnt, 0, nPrimitiveCnt);
	}
	else
	{
		pGraphic->GetDevice()->DrawPrimitive(g_PrimitiyType[ePrimitiveType], 0, nPrimitiveCnt);
	}
}
