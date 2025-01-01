#pragma once
#include <EngineBase/EngineMath.h>

struct EngineVertex
{
	float4 POSITION;
	float4 TEXCOORD; // UV값이라고 불리는 존재로 텍스처가 매핑되는 비율을 지정해줍니다.
	float4 COLOR;
};
