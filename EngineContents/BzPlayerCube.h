#pragma once
#include <EngineCore/Actor.h>

class ABzPlayerCube : public APawn
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
	void ApplyRecoilAnimation(FVector _Direction, float _Speed, float _DeltaTime);
	void Skl_Rockfall();
	void Skl_HomingProj();

private:
	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UBzRendererDefault> RendererFront;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	std::shared_ptr<class UCollision> Collision;
	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	float MoveSpeed =300.f;
	FVector forwardVector = GetActorForwardVector();
	std::shared_ptr<class ACameraActor> Camera ;
	FVector diff = { 0.f,0.f,0.f };


	FVector OrgScale = { 0.f,0.f,0.f };

	FVector FireRot = {0.f,0.f,0.f};
	bool Skl_RockfallOn;
};

