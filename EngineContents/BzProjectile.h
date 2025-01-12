#pragma once
#include <EngineCore/Actor.h>

class ABzProjectile : public AActor
{
public:
	ABzProjectile();
	~ABzProjectile(){}
	void SetPlayer(std::shared_ptr<class ABzPlayerCube> _name);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//FVector CalculateMoveDirection(float _DeltaTime);
	FVector CalculateMoveVelocity(float _DeltaTime);
	FVector CalculateMoveAcceleration(float _DeltaTime);
	//void ForceGravity(const float& dt);


private:
	std::shared_ptr<class ABzPlayerCube> Player = nullptr;

	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;

	float Speed = 1000.f;
	//FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	FVector ForwardDir = {0.f,0.f,0.f};
	FVector MoveDirection = {0.f,0.f,0.f};
	//FVector PrevPos = { 0.f,0.f,0.f };
	//FVector PrevVel;

	//FVector Velocity = FVector{ 1.f,0.f,0.f };
	//FVector Acceleration = FVector{ 0.f,1.f,0.f };
	FVector Gravity = FVector(0.0f, -3.8f, 0.0f);
};

