#pragma once
#include <EngineCore/Actor.h>
#include "BzEnemy.h"


class ABzEnemyCubeBig : public ABzEnemy
{
public:
	ABzEnemyCubeBig();
	~ABzEnemyCubeBig();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Ani_Idle(float _DeltaTime);

	void Physics(float _DeltaTime);


private:
	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

	float rotationAngle = 0.f;
	float jumpHeight = 0.f;
	FVector gravity = { 0.f,-2.f,0.f };
	FVector vel = { 0.f,1.f,0.f };
	float radius = 0;
	FVector pos = {};
};

