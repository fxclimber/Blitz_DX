#pragma once
#include <EngineBase/EngineMath.h>
#include "EngineInputLayOutInfo.h"

struct FEngineVertex
{
	// 모든 버텍스는 자신의 레이아웃 정보를 가지고 있어야 한다.
	friend class EngineVertexInit;
	inline static UEngineInputLayOutInfo Info;// inline 으로 바꾸니까, ENGINEAPI 안됬음 

	float4 POSITION;
	float4 TEXCOORD; // UV값이라고 불리는 존재로 텍스처가 매핑되는 비율을 지정해줍니다.
	float4 COLOR;
};


