#pragma once
#include <EngineCore/Renderer.h>

struct FMyColor
{
	float4 Albedo;
};

// Ό³Έν :
class MyCustomRenderer : public URenderer
{
public:
	// constrcuter destructer
	MyCustomRenderer();
	~MyCustomRenderer();

	// delete Function
	MyCustomRenderer(const MyCustomRenderer& _Other) = delete;
	MyCustomRenderer(MyCustomRenderer&& _Other) noexcept = delete;
	MyCustomRenderer& operator=(const MyCustomRenderer& _Other) = delete;
	MyCustomRenderer& operator=(MyCustomRenderer&& _Other) noexcept = delete;

protected:

private:
	FMyColor MyColor;
};

