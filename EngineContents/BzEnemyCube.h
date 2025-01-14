#pragma once
#include <EngineCore/Actor.h>
#include "BzEnemy.h"
#include <EngineBase/EngineRandom.h>

class ABzEnemyCube : public ABzEnemy
{
public:
	ABzEnemyCube();
	~ABzEnemyCube();
	void SetPlayer(std::shared_ptr<class ABzPlayerCube> _name);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Ani_Idle(float _DeltaTime);

	void Physics(float _DeltaTime);
	bool CheckAttackDistance(float _DeltaTime , float _speed);
	float GetRandom(float _x);
private:
	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;
	class ABzPlayerCube* Player = nullptr;

	float rotationAngle = 0.f;
	float jumpHeight = 0.f;
	FVector gravity = { 0.f,-2.f,0.f };
	FVector vel = { 0.f,1.f,0.f };
	float radius = 0;
	FVector pos = {};

	float AttackDistance;
	FVector Attackdir;
	FVector AttackPlayerPos;

	UEngineRandom random;
	float randomResult = 0;

};

