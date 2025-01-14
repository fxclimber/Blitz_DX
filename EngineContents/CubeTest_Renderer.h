#pragma once
#include <EngineCore/Renderer.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>

struct FCubeTestColor
{
	float4 Albedo;
};

struct FCubeTestVertex
{
	float4 POSITION;
	float4 UV;
	float4 COLOR;
};

enum class CubeTestPivotType
{
	Bottom,
	Top,
	Center,
};


class UCubeTest_Renderer : public URenderer
{
public:
	UCubeTest_Renderer();
	~UCubeTest_Renderer(){}
	void SetPivot(CubeTestPivotType _pivot);

private:
	FCubeTestColor TestColor;
};

