#include "PreCompile.h"
#include "BzEnemYCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include <EngineBase/EngineMath.h>

ABzEnemyCube::ABzEnemyCube()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 300.f,300.f,300.f });
	float YY = Renderer->GetTransformRef().Scale.Y;
	Renderer->SetWorldLocation({ 0.f,YY,0.f });
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "CheckUP.png");

	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Enemy");
	Collision->SetScale3D(Renderer->GetTransformRef().WorldScale);
	Collision->SetCollisionType(ECollisionType::OBB);

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor()->Destroy();
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

	radius = GetActorTransform().Scale.X;
	FVector RotationDelta(0.f, 30.f * _DeltaTime, 0.f); // 초당 100도 회전
	//AddActorRotation(RotationDelta);

	//Ani_Idle(_DeltaTime);
	//Physics(_DeltaTime);

}

void ABzEnemyCube::Ani_Idle(float _DeltaTime)
{
	rotationAngle = sinf(_DeltaTime) * 45.0f;
	FVector rotZ = {0.f,rotationAngle,0.f};
	AddActorRotation(rotZ);

	jumpHeight = sinf(_DeltaTime) * 50.0f;
	FVector jump = {0.f,jumpHeight,0.f};
	//AddActorLocation(jump);

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


