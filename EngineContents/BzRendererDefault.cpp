#include "PreCompile.h"
#include "BzRendererDefault.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <d3d11.h>
#include <wrl/client.h> // ComPtr »ç¿ë
#include <EngineCore/EngineTexture.h>




UBzRendererDefault::~UBzRendererDefault()
{
}


UBzRendererDefault::UBzRendererDefault()
{
    
    CreateRenderUnit();
    SetMesh("Cube");
    SetMaterial("BzDefault");
    TestColor.Albedo = float4(0.0f, 0.7f, 0.3f, 1.0f);
    GetRenderUnit().ConstantBufferLinkData("FBzColor", TestColor);
    GetRenderUnit().SetTexture("bz_texture0", "wall.jpg");

    //----------------------µª½º Å×½ºÆ® 
    // µª½º ÅØ½ºÃ³ 
    //D3D11_TEXTURE2D_DESC depthTexDesc = {};
    //depthTexDesc.Width = 1024;
    //depthTexDesc.Height = 1024;
    //depthTexDesc.MipLevels = 1;
    //depthTexDesc.ArraySize = 1;
    //depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    //depthTexDesc.SampleDesc.Count = 1;
    //depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
    //depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    //UEngineTexture depthTexture;
    //depthTexture.ResCreate(depthTexDesc);

    //// µª½º ½ºÅÙ½Ç »óÅÂ 
    //D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
    //depthStencilDesc.DepthEnable = TRUE;
    //depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    //depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    //depthStencilDesc.StencilEnable = FALSE;

    //Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
    //UEngineCore::GetDevice().GetDevice()->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
    //UEngineCore::GetDevice().GetContext()->OMSetDepthStencilState(depthStencilState.Get(), 0);

    //// ¹ÙÀÎµù-·»´õÅ¸°Ù,µª½ººä
    //ID3D11RenderTargetView* rtv = depthTexture.GetRTV();
    //UEngineCore::GetDevice().GetContext()->OMSetRenderTargets(1, &rtv, depthTexture.GetDSV()
    //);


}
