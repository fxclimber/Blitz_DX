#include "PreCompile.h"
#include "CubeTest_Renderer.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <d3d11.h>
#include <wrl/client.h> // ComPtr »ç¿ë
#include <EngineCore/EngineTexture.h>
#include <EngineCore/SceneComponent.h>


UCubeTest_Renderer::UCubeTest_Renderer()
{
    CreateRenderUnit();
    SetMesh("CubeTest");
    SetMaterial("CubeTestMaterial");
    TestColor.Albedo = float4(0.0f, 0.7f, 0.3f, 1.0f);
    GetRenderUnit().ConstantBufferLinkData("FCubeTestColor", TestColor);
    //GetRenderUnit().SetTexture("bz_texture0", "CheckUV.png");
}
void UCubeTest_Renderer::SetPivot(CubeTestPivotType _pivot)
{
    FVector scale = GetWorldScale3D();
    FVector loc = { 0.f,0.f,0.f };

    switch (_pivot)
    {
    case CubeTestPivotType::Center:
        loc = { 0.f,0.f,0.f };
        AddRelativeLocation(loc);
        break;
    case CubeTestPivotType::Bottom:
        loc = { 0.f,scale.Y,0.f };
        AddRelativeLocation(loc);
        break;
    case CubeTestPivotType::Top:
        loc = { 0.f,-scale.Y / 2,0.f };
        AddRelativeLocation(loc);
        break;

    default:
        break;
    }

}
