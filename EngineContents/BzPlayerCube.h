#pragma once
#include <EngineCore/Actor.h>

class ABzPlayerCube : public AActor
{
public:
	ABzPlayerCube();
	~ABzPlayerCube();



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
	std::shared_ptr<class ABzProjectile> Proj;

	std::shared_ptr<class UCollision> Collision;
	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	FVector forwardVector = GetActorForwardVector();

};

