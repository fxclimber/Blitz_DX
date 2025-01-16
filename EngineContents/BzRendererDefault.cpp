#include "PreCompile.h"
#include "BzRendererDefault.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <d3d11.h>
#include <wrl/client.h> // ComPtr »ç¿ë
#include <EngineCore/EngineTexture.h>
#include <EngineCore/SceneComponent.h>

UBzRendererDefault::~UBzRendererDefault()
{
}

UBzRendererDefault::UBzRendererDefault()
{
    {
        CreateRenderUnit();
        SetMesh("Cube");
        SetMaterial("BzDefault");
        TestColor.Albedo = float4(0.0f, 0.7f, 0.3f, 1.0f);
        GetRenderUnit().ConstantBufferLinkData("FBzColor", TestColor);
        GetRenderUnit().SetTexture("bz_texture0", "b22.jpg");
    }
}

void UBzRendererDefault::SetPivot(PivotType _pivot)
{
    FVector scale = GetWorldScale3D();
    FVector loc = { 0.f,0.f,0.f };

    switch (_pivot)
    {
    case PivotType::Center:
        loc = { 0.f,0.f,0.f };
        AddRelativeLocation(loc);
        break;
    case PivotType::Bottom:
        loc = { 0.f,scale.Y,0.f };
        AddRelativeLocation(loc);
        break;
    case PivotType::Top:
        loc = { 0.f,-scale.Y/2,0.f };
        AddRelativeLocation(loc);
        break;

    default:
        break;
    }

}
