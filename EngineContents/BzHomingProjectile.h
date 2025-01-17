#pragma once
#include <EngineCore/Actor.h>

class ABzHomingProjectile : public AActor
{
public:
	ABzHomingProjectile();
	~ABzHomingProjectile(){}
	void SetPlayer(class ABzPlayerCube* _name);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//FVector CalculateMoveDirection(float _DeltaTime);
	//FVector CalculateMoveVelocity(float _DeltaTime);
	FVector CalculateMoveAcceleration(float _DeltaTime);
	//void ForceGravity(const float& dt);
	void UpdatePositionAndOrientation(float _DeltaTime);

private:
	class ABzPlayerCube* Player = nullptr;
	class ABzEnemyCube* Enemy1 = nullptr;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

	float Speed = 1000.f;
	FVector ForwardDir = {0.f,0.f,0.f};
	FVector MoveDirection = {0.f,0.f,0.f};
	FVector Gravity = FVector(0.0f, -3.8f, 0.0f);
};

