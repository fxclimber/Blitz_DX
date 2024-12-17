#pragma once
#include "ActorComponent.h"

// #include "PreCompile.h"

// Ό³Έν :
class USceneComponent : public UActorComponent
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

protected:

private:

	FTransform Transform;

	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

