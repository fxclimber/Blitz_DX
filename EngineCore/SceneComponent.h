#pragma once
#include "ActorComponent.h"

// #include "PreCompile.h"

// 설명 :
class USceneComponent : public UActorComponent
{
	friend class AActor;

	// Local 부모영향 받음
	// World 안받음
	// 아무것도 없음 안받음

public:
	// constrcuter destructer
	USceneComponent();
	virtual ~USceneComponent() = 0;

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	ENGINEAPI void ComponentTick(float _DeltaTime) override;

	void AddRelativeLocation(const FVector& _Value)
	{
		Transform.Location += _Value;
		TransformUpdate();
	}

	void SetWorldLocation(const FVector& _Value)
	{
		IsAbsolute = true;
		Transform.Location = _Value;
		TransformUpdate();
	}

	void SetRelativeLocation(const FVector& _Value)
	{
		Transform.Location = _Value;
		TransformUpdate();
	}


	void AddRotation(const FVector& _Value)
	{
		Transform.Rotation += _Value;
		TransformUpdate();
	}

	void SetRotation(const FVector& _Value)
	{
		Transform.Rotation = _Value;
		TransformUpdate();
	}

	void SetScale3D(const FVector& _Value)
	{
		IsAbsolute = true;
		Transform.Scale = _Value;
		TransformUpdate();
	}

	// local
	void SetRelativeScale3D(const FVector& _Value)
	{
		// 절대값이라는 뜻
		// 이게 true가 되면 부모가 있건 없건
		// 100 100 100
		// 10 10 10
		// 나는 무조건 이값에 해당하는 행렬이 되어야 한다는 뜻으로 
		Transform.Scale = _Value;
		Transform.Scale.W = 0.0f;
		TransformUpdate();
	}

	FVector GetWorldScale3D()
	{
		return Transform.WorldScale;
	}


	FTransform& GetTransformRef()
	{
		return Transform;
	}


	ENGINEAPI void SetupAttachment(std::shared_ptr<USceneComponent> _Parent);

	void SetupAttachment(USceneComponent* _Parent);

	ENGINEAPI void TransformUpdate();

protected:
	bool IsAbsolute = false;

	FTransform Transform;

	ENGINEAPI void BeginPlay() override;

	void ParentMatrixCheck();

private:
	USceneComponent* Parent = nullptr;
	std::list<std::shared_ptr<USceneComponent>> Childs;
};

