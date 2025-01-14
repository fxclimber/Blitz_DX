#include "PreCompile.h"
#include "EngineRenderTarget.h"

UEngineRenderTarget::UEngineRenderTarget()
{
    TargetUnit.SetMesh("FullRect");
    TargetUnit.SetMaterial("TargetMerge");
}

UEngineRenderTarget::~UEngineRenderTarget()
{
}


void UEngineRenderTarget::CreateTarget(float4 _Scale, float4 _ClearColor /*= float4::NONE*/, DXGI_FORMAT _Format /*= DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT*/)
{
    ClearColor = _ClearColor;

    std::shared_ptr<class UEngineTexture> NewTarget = std::make_shared<UEngineTexture>();

    // 랜더타겟이라는 구조로 변경될 겁니다. 
    D3D11_TEXTURE2D_DESC Desc = { 0 };
    Desc.ArraySize = 1;
    Desc.Width = _Scale.iX();
    Desc.Height = _Scale.iY();
    // 3바이트 실수 1바이트 정수를 스탠실 값이라고 합니다.
    Desc.Format = _Format;

    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;

    // 이렇게 만드는 녀석들은

    Desc.MipLevels = 1;
    Desc.Usage = D3D11_USAGE_DEFAULT;
    Desc.CPUAccessFlags = 0;
    // 여기에 그려질수도 있고 
    // 그려진 걸 쉐이더에서 시용할수 도 있다.
    Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

    NewTarget->ResCreate(Desc);
    NewTarget->Size = _Scale;

    ArrRTVs.push_back(NewTarget->GetRTV());
    ArrTexture.push_back(NewTarget);
}


void UEngineRenderTarget::CreateTarget(Microsoft::WRL::ComPtr<ID3D11Texture2D> _Texture2D)
{
	std::shared_ptr<class UEngineTexture> NewTarget = std::make_shared<UEngineTexture>();
	NewTarget->ResCreate(_Texture2D);


    if (nullptr == NewTarget->GetRTV())
    {
        MSGASSERT("랜더타겟 뷰가 존재하지 않는 랜더타겟 입니다.");
    }
    ;

    ArrRTVs.push_back(NewTarget->GetRTV());

    ArrTexture.push_back(NewTarget);
}

// 몇번째 타겟의 사이즈로 깊이버퍼를 만들거냐 입니다.
void UEngineRenderTarget::CreateDepth(int _Index)
{
    if (ArrTexture.size() <= _Index)
    {
        MSGASSERT("존재하지 않는 텍스처 인덱스로 깊이버퍼를 만들려고 했습니다.");
    }

    FVector Size = ArrTexture[_Index]->GetTextureSize();

    // 랜더타겟이라는 구조로 변경될 겁니다. 
    D3D11_TEXTURE2D_DESC Desc = { 0 };
    Desc.ArraySize = 1;
    Desc.Width = Size.iX();
    Desc.Height = Size.iY();
    // 3바이트 실수 1바이트 정수를 스탠실 값이라고 합니다.
    Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;

    Desc.MipLevels = 1;
    Desc.Usage = D3D11_USAGE_DEFAULT;
    Desc.CPUAccessFlags = 0;
    Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

    DepthTexture = std::make_shared<UEngineTexture>();
    DepthTexture->ResCreate(Desc);

}

void UEngineRenderTarget::Clear()
{
    for (size_t i = 0; i < ArrRTVs.size(); i++)
    {
        UEngineCore::GetDevice().GetContext()->ClearRenderTargetView(ArrRTVs[i], ClearColor.Arr1D);
    }
    UEngineCore::GetDevice().GetContext()->ClearDepthStencilView(DepthTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void UEngineRenderTarget::Setting()
{
    //ID3D11RenderTargetView* RTV = UEngineCore::GetDevice().GetRTV();
    //ID3D11RenderTargetView* ArrRtv[16] = { 0 };
    // ArrRtv[0] = RTV; // SV_Target0
    UEngineCore::GetDevice().GetContext()->OMSetRenderTargets(1, &ArrRTVs[0], DepthTexture->GetDSV());
}

// 어던 랜더타겟의 요소를 다른 랜더타겟에 복사한다.
// 지우고 복사한다.
void UEngineRenderTarget::CopyTo(std::shared_ptr<UEngineRenderTarget> _Target)
{
    _Target->Clear();
    MergeTo(_Target);
}

void UEngineRenderTarget::MergeTo(std::shared_ptr<UEngineRenderTarget> _Target)
{
    _Target->Setting();
    TargetUnit.SetTexture("MergeTex", ArrTexture[0]);
    TargetUnit.Render(nullptr, 0.0f);
}