#include "PreCompile.h"
#include "BzProjectile.h"
#include <EngineCore/Collision.h>
#include "BzPlayerCube.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>


ABzProjectile::ABzProjectile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 50.f,5.f,5.f });
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "CheckUP.png");

	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Proj");
	Collision->SetScale3D({ 30,15.f,15.f });
	// Collision->AddRelativeLocation({30.f,0.f,0.f});
	Collision->SetCollisionType(ECollisionType::OBB);

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			//_Other->GetActor()->Destroy();
			UEngineDebug::OutPutString("Enter");
		});

}

ABzProjectile::~ABzProjectile()
{
}

void ABzProjectile::BeginPlay()
{
	AActor::BeginPlay();

	MoveDirection = Player->GetActorTransform().Rotation;
	//FVector SpawnPos = Player->GetActorLocation();
	auto fire = Player->GetFire();
	const auto& pos = fire.get()->GetTransformRef().WorldLocation;
	const auto& scale = fire.get()->GetTransformRef().WorldScale;
	FVector SpawnPos = FVector(pos.X, pos.Y, pos.Z);
	FVector SpawnScale = FVector(scale.X, scale.Y, scale.Z);
	//SpawnPos = SpawnPos+ FVector{0.f,0.f,scale.Z * 2 };

	fire.get()->GetTransformRef().Location;
	//SpawnPos += {0.f, 100.f, 0.f};
	SetActorRotation(MoveDirection);
	SetActorLocation(SpawnPos);
	//ForwardDir = GetActorForwardVector();
	ForwardDir = GetActorRightVector();
}



void ABzProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//CalculateMoveDirection(_DeltaTime);
	AddRelativeLocation(ForwardDir * _DeltaTime * Speed);

	//Collision->CollisionCheck();
}

void ABzProjectile::SetPlayer(std::shared_ptr<class ABzPlayerCube> _name)
{
	Player = _name;
}


FVector ABzProjectile::CalculateMoveDirection(float _DeltaTime)
{
	AddActorLocation(MoveDirection);

	if (MoveDirection.X != 0.0f || MoveDirection.Z != 0.0f)
	{
		float targetAngle = atan2(-MoveDirection.Z, MoveDirection.X) * UEngineMath::R2D;
		float currentAngle = GetActorTransform().Rotation.Y;

		float deltaAngle = targetAngle - currentAngle;
		if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
		if (deltaAngle < -180.0f) deltaAngle += 360.0f;

		float lerpedAngle = currentAngle + deltaAngle * _DeltaTime * 5.0f; // 회전 속도 계수
		AddActorRotation(FVector(0.0f, lerpedAngle - currentAngle, 0.0f));
	}

	return MoveDirection;
}
