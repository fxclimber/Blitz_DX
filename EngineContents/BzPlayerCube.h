#pragma once
#include <EngineCore/Actor.h>



class ABzPlayerCube : public APawn
{
public:
	ABzPlayerCube();
	~ABzPlayerCube();
	class UBzRendererDefault* GetFire()
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
	void ApplyTilemap();

	void Skl_Rockfall();
	void Skl_ArcStone();
	void Skl_Missile();
	void Skl_Dash(FVector _Direction, float _Speed, float _DeltaTime);
	void Atk();

private:
	std::shared_ptr<class UBzRendererDefault> Renderer;
	std::shared_ptr<class UCollision> Collision;
	class UBzRendererDefault* RendererFront;
	class UTimeEventComponent* TimeEventComponent;

	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);
	float MoveSpeed =500.f;
	FVector forwardVector = GetActorForwardVector();
	class ACameraActor* Camera ;
	FVector diff = { 0.f,0.f,0.f };
	int fov = 70.f;


	FVector OrgScale = { 0.f,0.f,0.f };

	FVector FireRot = {0.f,0.f,0.f};
	bool Skl_RockfallOn;
	bool IsDash = false;
	float DashTime = 0.0f;

};

