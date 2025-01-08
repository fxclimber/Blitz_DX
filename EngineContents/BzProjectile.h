#pragma once
#include <EngineCore/Actor.h>

class ABzProjectile : public AActor
{
public:
	ABzProjectile();
	~ABzProjectile();
	void SetPlayer(std::shared_ptr<class ABzPlayerCube> _name);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	FVector CalculateMoveDirection(float _DeltaTime);

private:
	std::shared_ptr<class ABzPlayerCube> Player;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

	float Speed = 1000.f;
	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	FVector ForwardDir = {0.f,0.f,0.f};

};

