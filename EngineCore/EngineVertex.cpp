#include "PreCompile.h"
#include "EngineVertex.h"

// 정적 변수의 올바른 정의 (ENGINEAPI 제거)
UEngineInputLayOutInfo FEngineVertex::Info;

ENGINEAPI UEngineInputLayOutInfo& FEngineVertex::GetInfo()
{
    return Info;
}

class EngineVertexInit
{
public:
    EngineVertexInit()
    {
        FEngineVertex::Info.AddInputLayout("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
        FEngineVertex::Info.AddInputLayout("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
        FEngineVertex::Info.AddInputLayout("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
    }
};

// 정적 객체 생성
EngineVertexInit InitObject;
