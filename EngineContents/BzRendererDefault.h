#pragma once
#include <EngineCore/Renderer.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>


struct FBzColor
{
	float4 Albedo;
};

struct FVertex
{
	float4 POSITION;
	float4 UV;
	float4 COLOR;
};

enum class PivotType
{
	Bottom,
	Top,
	Center,
};




class UBzRendererDefault : public URenderer
{
public:
	UBzRendererDefault();
	~UBzRendererDefault();

void SetPivot(PivotType _pivot);


protected:

private:
	FBzColor TestColor;


};

