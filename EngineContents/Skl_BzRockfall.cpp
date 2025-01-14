#include "PreCompile.h"
#include "Skl_BzRockfall.h"
#include <EngineCore/Collision.h>
#include "BzPlayerCube.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineRandom.h>


ASkl_BzRockfall::ASkl_BzRockfall()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 75.f,75.f,105.f });
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "GridBlue.png");

	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionProfileName("Skl_BzRockfall");
	Collision->SetCollisionType(ECollisionType::AABB);

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			//_Other->GetActor()->Destroy();
			//UEngineDebug::OutPutString("Enter");
		});

}

ASkl_BzRockfall::~ASkl_BzRockfall()
{
}

void ASkl_BzRockfall::BeginPlay()
{
	AActor::BeginPlay();

	Player = dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());

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
		//SetActorRotation(rot);
		//SetActorLocation(SpawnPos);
		ForwardDir = GetActorForwardVector();
	}


}

void ASkl_BzRockfall::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CalculateMoveAcceleration(_DeltaTime);
	ForwardDir += Gravity * _DeltaTime;
	AddActorLocation(ForwardDir * _DeltaTime * Speed);

}

FVector ASkl_BzRockfall::CalculateMoveAcceleration(float _DeltaTime)
{
	FVector pos = GetActorLocation();
	static const float coef_res = 0.6f;
	static const float coef_friction = 0.7f;

	if (pos.Y <= 2.0f)
	{
		if (ForwardDir.Y <= 0.0f)
		{
			ForwardDir.Y *= -coef_res;
		}
		ForwardDir.X *= coef_friction;
		ForwardDir.Z *= coef_friction;

		if (pos.Y < 0.0f)
		{
			pos.Y = 0.0f;
			SetActorLocation(pos);// 지면- Y 위치 고정
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

		float lerpedYaw = currentRotation.Y + deltaYaw * _DeltaTime * 3.0f; // 속도 계수 3.0f
		float lerpedPitch = currentRotation.X + deltaPitch * _DeltaTime * 103.0f;

		FVector newRotation(lerpedPitch, lerpedYaw, currentRotation.Z); // Roll 고정
		SetActorRotation(newRotation);
	}


	return ForwardDir;
}




float ASkl_BzRockfall::GetRandom(float _x)
{
	float x = this->random.Randomfloat(-_x, _x);
	float y = UEngineMath::Clamp(x, -0.1f,-1.f);
	return y;
}
