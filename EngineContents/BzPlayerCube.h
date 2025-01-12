#pragma once
#include <EngineCore/Actor.h>

class ABzPlayerCube : public AActor
{
public:
	ABzPlayerCube();
	~ABzPlayerCube();
	std::shared_ptr<class UBzRendererDefault> GetFire()
	{
		return RendererFront;
	}
	FVector GetFireRot()
	{
		return FireRot;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	FVector CalculateMoveDirection(float _DeltaTime);


private:
	std::shared_ptr<class USpriteRenderer> LogoRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UBzRendererDefault> RendererFront;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	std::shared_ptr<class UCollision> Collision;
	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	float MoveSpeed =300.f;
	FVector forwardVector = GetActorForwardVector();
	std::shared_ptr<class ACameraActor> Camera ;
	FVector diff = { 0.f,0.f,0.f };

	FVector FireRot = {0.f,0.f,0.f};
};

