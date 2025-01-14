#include "PreCompile.h"
#include "BzProjectile.h"
#include <EngineCore/Collision.h>
#include "BzPlayerCube.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineBase/EngineMath.h>

ABzProjectile::ABzProjectile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 15.f,15.f,85.f });
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "CheckUP.png");

	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionProfileName("Proj");
	Collision->SetCollisionType(ECollisionType::OBB);

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor()->Destroy();
			UEngineDebug::OutPutString("Enter");
		});

}

void ABzProjectile::BeginPlay()
{
	AActor::BeginPlay();

	{
		MoveDirection = Player->GetActorTransform().Rotation;

		auto fire = Player->GetFire();
		const auto& pos = fire.get()->GetTransformRef().WorldLocation;
		const auto& scale = fire.get()->GetTransformRef().WorldScale;
		const auto& rotRender = fire.get()->GetTransformRef().Rotation;
		FVector rot = Player->GetActorTransform().Rotation;
		rot -= rotRender;


		FVector SpawnPos = FVector(pos.X, pos.Y, pos.Z);
		FVector SpawnScale = FVector(scale.X, scale.Y, scale.Z);

		fire.get()->GetTransformRef().Location;
		SetActorRotation(rot);
		SetActorLocation(SpawnPos);
		ForwardDir = GetActorForwardVector();

	}
	//Velocity = ForwardDir * Speed;
}



void ABzProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//PrevPos = GetActorLocation();

	CalculateMoveAcceleration(_DeltaTime);
	ForwardDir += Gravity *_DeltaTime;
	//AddRelativeLocation(ForwardDir * _DeltaTime * Speed);
	AddActorLocation(ForwardDir * _DeltaTime * Speed);
	std::string fireRotString =
		"FireRot: (X: " + std::to_string(ForwardDir.X) +
		", Y: " + std::to_string(ForwardDir.Y) +
		", Z: " + std::to_string(ForwardDir.Z) + ")";
	UEngineDebug::OutPutString(fireRotString);
}


FVector ABzProjectile::CalculateMoveAcceleration(float _DeltaTime)
{
	FVector pos = GetActorLocation();
	static const float coef_res = 0.6f;      
	static const float coef_friction = 0.7f; 

	if (pos.Y <= 2.0f)
	{
		// Y축 반발력 적용 (지면에 닿고 Y 방향 속도가 음수일 때)
		if (ForwardDir.Y <= 0.0f)
		{
			ForwardDir.Y *= -coef_res;
		}
		ForwardDir.X *= coef_friction;
		ForwardDir.Z *= coef_friction;
		
		if (pos.Y < 0.0f)
		{
			pos.Y = 0.0f;
			SetActorLocation(pos);// 지면에 닿은 경우 Y 위치 고정
		}
	}
	if (!(ForwardDir.X == 0.0f && ForwardDir.Y == 0.0f && ForwardDir.Z == 0.0f))
	{
		FVector normalizedDir = ForwardDir.NormalizeReturn();

		float targetYaw = atan2(normalizedDir.X, normalizedDir.Z); // XZ 평면 기준
		float targetPitch = atan2(normalizedDir.Y, sqrt(normalizedDir.X * normalizedDir.X + normalizedDir.Z * normalizedDir.Z)); // Y축 포함

		FVector currentRotation = GetActorTransform().Rotation;

		float deltaYaw = targetYaw - currentRotation.Y;
		float deltaPitch = targetPitch - currentRotation.X;

		if (deltaYaw > DirectX::XM_PI) deltaYaw -= DirectX::XM_2PI;
		if (deltaYaw < -DirectX::XM_PI) deltaYaw += DirectX::XM_2PI;

		if (deltaPitch > DirectX::XM_PI) deltaPitch -= DirectX::XM_2PI;
		if (deltaPitch < -DirectX::XM_PI) deltaPitch += DirectX::XM_2PI;

		// 부드러운 회전 적용
		float lerpedYaw = currentRotation.Y + deltaYaw * _DeltaTime * 3.0f; // 속도 계수 3.0f
		float lerpedPitch = currentRotation.X + deltaPitch * _DeltaTime * 103.0f;

		// 새로운 회전값 설정
		FVector newRotation(lerpedPitch, lerpedYaw, currentRotation.Z); // Roll 고정
		SetActorRotation(newRotation);
	}




	return ForwardDir;
}

void ABzProjectile::SetPlayer(class ABzPlayerCube* _name)
{
	Player = _name;
}


