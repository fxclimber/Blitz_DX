#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineRandom.h>


class ASkl_BzRockfall : public AActor
{
public:
	ASkl_BzRockfall();
	~ASkl_BzRockfall();


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	float GetRandom(float _x);
	bool CheckAttackDistance(float _DeltaTime, float _speed);
	FVector CalculateMoveAcceleration(float _DeltaTime);

private:
	class ABzPlayerCube* Player = nullptr;
	class ABzEnemyCube* Enemy = nullptr;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

	float Speed = 1000.f;
	FVector ForwardDir = { 0.f,0.f,0.f };
	FVector MoveDirection = { 0.f,0.f,0.f };
	FVector Gravity = FVector(0.0f, -3.8f, 0.0f);

	UEngineRandom random;
	float randomResult = 0;

	float AttackDistance;
	FVector Attackdir;
	FVector AttackPlayerPos;


};

