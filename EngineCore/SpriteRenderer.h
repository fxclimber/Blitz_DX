#pragma once
#include "Renderer.h"

// Ό³Έν :
class USpriteRenderer : public URenderer
{
public:
	// constrcuter destructer
	ENGINEAPI USpriteRenderer();
	ENGINEAPI ~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	ENGINEAPI void SetSprite(std::string_view _Name, size_t _Index);

protected:
	void BeginPlay() override;

private:

};

