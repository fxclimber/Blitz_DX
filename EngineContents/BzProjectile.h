#pragma once
#include <EngineCore/Actor.h>
#include "BzClassManager.h"

class ABzProjectile : public AActor
{
public:
	ABzProjectile();
	~ABzProjectile(){}
	void SetPlayer(class ABzPlayerCube* _name);

	FVector Pos = FVector::ZERO;
	bool bActive = true;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//FVector CalculateMoveDirection(float _DeltaTime);
	FVector CalculateMoveVelocity(float _DeltaTime);
	FVector CalculateMoveAcceleration(float _DeltaTime);
	//void ForceGravity(const float& dt);

	void Differenciate(ABzClassManager& manager);
	bool IsColliding(class ABzEnemy* enemy);

private:
	class ABzPlayerCube* Player = nullptr;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

	float Speed = 1000.f;
	FVector ForwardDir = {0.f,0.f,0.f};
	FVector MoveDirection = {0.f,0.f,0.f};
	FVector Gravity = FVector(0.0f, -3.8f, 0.0f);
};

