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

	void AddLocation(const FVector& _Value)
	{
		Transform.Location += _Value;
		Transform.TransformUpdate();
	}

	void SetRelativeScale3D(const FVector& _Value)
	{
		Transform.Scale = _Value;
		Transform.TransformUpdate();
	}

	void SetLocation(const FVector& _Value)
	{
		Transform.Location = _Value;
		Transform.TransformUpdate();
	}

	FTransform& GetTransformRef()
	{
		return Transform;
	}

protected:
	FTransform Transform;

private:

	USceneComponent* Parent;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

