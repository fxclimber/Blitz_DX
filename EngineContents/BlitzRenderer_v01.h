#pragma once
#include <EngineCore/Renderer.h>

struct FMyColor
{
	float4 Albedo;
};


class BlitzRenderer_v01 : public URenderer
{
public:
	BlitzRenderer_v01();
	~BlitzRenderer_v01();

protected:

private:
	FMyColor myColor;


};

