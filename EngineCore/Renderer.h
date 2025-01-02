#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"

struct FUVValue
{
	float4 PlusUVValue;
};

// 설명 : 어떤 랜더링이든 할수 잇는 구조로 만들겠다.
// 랜더링이란 랜더러만 하는게 아닙니다. 3D
class URenderer : public USceneComponent
{
	friend class UEngineCamera;

public:
	// constrcuter destructer
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	ENGINEAPI void SetOrder(int _Order);
	ENGINEAPI void BeginPlay() override;
	ENGINEAPI virtual void Render(UEngineCamera* _Camera, float _DeltaTime);

	URenderUnit& GetRenderUnit(UINT  _Index);

	URenderUnit& CreateRenderUnit();

	void SetMesh(std::string_view _Name, UINT _Index = 0);
	void SetMaterial(std::string_view _Name, UINT _Index = 0);

private:

public:
	std::vector<URenderUnit> Units;
};

