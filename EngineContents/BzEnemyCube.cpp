#include "PreCompile.h"
#include "BzEnemyCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include <EngineBase/EngineMath.h>
#include "BzConst.h"

ABzEnemyCube::ABzEnemyCube()
{
	EEnemyTypeValue = EEnemyType::BzEnemyCube;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 50.f,100.f,20.f });
	Renderer->SetPivot(PivotType::Bottom);
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "CheckUP.png");


	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionProfileName("Enemy");
	Collision->SetCollisionType(ECollisionType::OBB);
	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			//_Other->GetActor()->Destroy();
			//UEngineDebug::OutPutString("Enter");
		});


}

ABzEnemyCube::~ABzEnemyCube()
{
}

void ABzEnemyCube::BeginPlay()
{
	AActor::BeginPlay();
	pos = GetActorLocation();
}

void ABzEnemyCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	BzConst::TotalTime += _DeltaTime;

	radius = GetActorTransform().Scale.X;
	FVector RotationDelta(0.f, 30.f * _DeltaTime, 0.f); // 초당 100도 회전
	//AddActorRotation(RotationDelta);

	Ani_Idle(_DeltaTime);
	//Physics(_DeltaTime);

}

void ABzEnemyCube::Ani_Idle(float _DeltaTime)
{
	float amplitude = 0.5f;
	float frequency = .15f;
	float rotationAngle = amplitude * sin(BzConst::TotalTime * frequency);
	FVector rotZ = {0.f,0.f,rotationAngle};
	AddActorRotation(rotZ);

	float jumpAmplitude = 142.f;
	float jumpFrequency = 0.05f;

	float normalizedTime = fmod(BzConst::TotalTime * jumpFrequency, 1.0f);

	// 포물선 식 계산
	float jumpHeight = jumpAmplitude * (-4.f * normalizedTime * (normalizedTime - 1.f));

	// 기준 위치에서 상대적으로 이동
	FVector currentLocation = GetActorLocation();
	FVector jumpOffset = FVector(0.f, jumpHeight, 0.f);
	FVector newLocation = pos + jumpOffset - FVector(0.f, currentLocation.Y - pos.Y, 0.f);

	AddActorLocation(newLocation - currentLocation);

}


void ABzEnemyCube::Physics(float _DeltaTime)
{
		//static const vec2 gravitY = vec2(0.0f, -9.8f);
		static const float coef_res = 0.7f; // coefficient of restitution
		static const float coef_friction = 0.99f; // friction (not phYsical)

		// numerical integration
		vel += gravity * _DeltaTime;
		pos += vel * _DeltaTime;

		// wall collision, friction
		if (1.0f - pos.X <= radius) // right wall
		{
			pos.X = 1.0f - radius;

			if (vel.X >= 0.0f)
				vel.X *= -1.0f * coef_res;
		}

		if (pos.X <= -1.0f + radius) // left wall
		{
			pos.X = -1.0f + radius;

			if (vel.X <= 0.0f)
				vel.X *= -1.0f * coef_res;
		}

		if (pos.Y <= -1.0f + radius) // ground
		{
			pos.Y = -1.0f + radius;

			if (vel.Y <= 0.0f)
				vel.Y *= -1.0f * coef_res;

			vel.X *= coef_friction;
		}
		AddActorLocation(pos);
}


