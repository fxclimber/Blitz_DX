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
    {
        CreateRenderUnit();
        SetMesh("Cube");
        SetMaterial("BzDefault");
        TestColor.Albedo = float4(0.0f, 0.7f, 0.3f, 1.0f);
        GetRenderUnit().ConstantBufferLinkData("FBzColor", TestColor);
        GetRenderUnit().SetTexture("bz_texture0", "CheckUV.png");
    }


}
