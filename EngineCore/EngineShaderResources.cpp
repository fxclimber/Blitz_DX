#include "PreCompile.h"
#include "EngineShaderResources.h"

UEngineShaderResources::UEngineShaderResources()
{
}

UEngineShaderResources::~UEngineShaderResources()
{
}

void UEngineShaderResources::CreateConstantBufferRes(std::string_view _Name, UEngineConstantBufferRes _Res)
{
	if (true == ConstantBufferRess.contains(_Name.data()))
	{
		MSGASSERT("같은 이름 상수버퍼가 한 쉐이더에 2개가 존재합니다");
		return;
	}

	ConstantBufferRess[_Name.data()] = _Res;
}