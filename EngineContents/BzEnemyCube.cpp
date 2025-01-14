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
#include "BzplayerCube.h"
#include <EngineBase/EngineMath.h>

ABzEnemyCube::ABzEnemyCube()
{
	EEnemyTypeValue = EEnemyType::BzEnemyCube;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 50.f,100.f,50.f });
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
	
	Player = dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());

	//Player = std::shared_ptr<APawn>(GetWorld()->GetMainPawn());
	//PlayerP = static_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());
	//Player = dynamic_cast<ABzPlayerCube*>(pawn);
}

ABzEnemyCube::~ABzEnemyCube()
{
}

void ABzEnemyCube::BeginPlay()
{
	AActor::BeginPlay();

	APawn* Ptr = GetWorld()->GetMainPawn();
	randomResult = GetRandom(2.f);

	//PlayerP = dynamic_cast<APawn*>(GetWorld()->GetMainPawn());
	pos = GetActorLocation();
}

void ABzEnemyCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	BzConst::TotalTime += _DeltaTime;

	radius = GetActorTransform().Scale.X;
	//FVector RotationDelta(0.f, 30.f * _DeltaTime, 0.f); // 초당 100도 회전

	//Ani_Idle(_DeltaTime);
	CheckAttackDistance(_DeltaTime , 500.f);

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
	float jumpHeight = jumpAmplitude * (-4.f * normalizedTime * (normalizedTime - 1.f));
	FVector currentLocation = GetActorLocation();
	FVector jumpOffset = FVector(0.f, jumpHeight, 0.f);
	FVector newLocation = pos + jumpOffset - FVector(0.f, currentLocation.Y - pos.Y, 0.f);
	//AddActorLocation(newLocation - currentLocation);
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

void ABzEnemyCube::SetPlayer(std::shared_ptr<class ABzPlayerCube> _name)
{
	//Player = _name;
}

bool ABzEnemyCube::CheckAttackDistance(float _DeltaTime, float _speed)
{
	if (nullptr != Player)
	{
		AttackPlayerPos = Player->GetActorLocation();
		Attackdir = AttackPlayerPos - GetActorLocation();
		AttackDistance = Attackdir.Length();
		Attackdir.Normalize();
		float speed = randomResult * _speed;
		//float speed = 100.f;

		{
			std::string ppp =
				"AttackDistance: (X: " + std::to_string(AttackDistance);
			UEngineDebug::OutPutString(ppp);
		}
		if (AttackDistance > 250.f)
		{
			FVector NormalizedDir = Attackdir;
			AddActorLocation(NormalizedDir * _DeltaTime * speed);
			{
				std::string aaa =
					"NormalizedDir: (X: " + std::to_string(NormalizedDir.X) +
					", Y: " + std::to_string(NormalizedDir.Y) +
					", Z: " + std::to_string(NormalizedDir.Z) + ")";
				UEngineDebug::OutPutString(aaa);
			}
		}
		//else if (AttackDistance <= 80.f)
		//{
		//	SetActorLocation(GetActorLocation());
		//}

		if (Attackdir.Z != 0.0f || Attackdir.X != 0.0f)
		{
			float targetAngle = atan2(-Attackdir.X, Attackdir.Z) * UEngineMath::R2D;
			float currentAngle = GetActorTransform().Rotation.Y;
			float deltaAngle = targetAngle - currentAngle;
			if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
			if (deltaAngle < -180.0f) deltaAngle += 360.0f;

			// 부드러운 회전
			float lerpedAngle = currentAngle + deltaAngle * _DeltaTime * 1.0f; 
			AddActorRotation(FVector(0.0f, lerpedAngle - currentAngle, 0.0f));
		}
	}
	return true;
}


float ABzEnemyCube::GetRandom(float _x) 
{
	float x = this->random.Randomfloat(-_x, _x);
	float y = UEngineMath::Clamp(x, 0.3f, x * 1.f);
	return y;
}
