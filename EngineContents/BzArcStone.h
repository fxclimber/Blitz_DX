#pragma once
#include <EngineCore/Actor.h>
#include "BzClassManager.h"

class ABzArcStone : public AActor
{
public:
	ABzArcStone();
	~ABzArcStone(){}
	void SetPlayer(class ABzPlayerCube* _name);

	FVector Pos = FVector::ZERO;
	bool bActive = true;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	FVector CalculateMoveAcceleration(float _DeltaTime);

	void KillEnemy();

	void Differenciate(ABzClassManager& manager);
	bool IsColliding(class ABzEnemy* enemy);

private:
	class ABzPlayerCube* Player = nullptr;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	//std::shared_ptr<class UCollision> Collision;

	class UCollision* Collision;

	float Speed = 2000.f;
	FVector ForwardDir = {0.f,0.f,0.f};
	FVector MoveDirection = {0.f,0.f,0.f};
	FVector Gravity = FVector(0.0f, -5.8f, 0.0f);
};

