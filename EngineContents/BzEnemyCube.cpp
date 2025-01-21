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
#include "BzGameMode_Intro.h"
#include "BzTileMap.h"
#include "BzClassManager.h"

ABzEnemyCube::ABzEnemyCube()
{
	//EEnemyTypeValue = EEnemyType::BzEnemyCube;

	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());
	Manager = GM->Manager;
	Manager->RegisterEnemy(this);

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D(Scale);
	Renderer->SetPivot(PivotType::Bottom);
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "test11.png");


	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	collisionList.push_back(Collision.get());
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionProfileName("Enemy");
	Collision->SetCollisionType(ECollisionType::OBB);
	Collision->SetCollisionStay([](UCollision* _This, UCollision* _Other)
		{
			FVector otherLocation = _Other->GetActor()->GetActorLocation();
			FVector thisLocation = _This->GetActor()->GetActorLocation();
			FVector reflectDir = otherLocation - thisLocation;
			float length = reflectDir.Length();

			if (length < 170.f)
			{
				_Other->GetActor()->AddActorLocation(reflectDir.NormalizeReturn()*5.f);
			}
		});
	
	Player = dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());

}

ABzEnemyCube::~ABzEnemyCube()
{
	Manager->RemoveEnemy(this);

}

void ABzEnemyCube::BeginPlay()
{
	AActor::BeginPlay();

	APawn* Ptr = GetWorld()->GetMainPawn();
	randomResult = GetRandom(2.f);

	pos = GetActorLocation();
}

void ABzEnemyCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	BzConst::TotalTime += _DeltaTime;

	radius = GetActorTransform().Scale.X;

	AvoidWall(_DeltaTime);// very strange !!!! 
	CheckAttackDistance(_DeltaTime , 500.f);
	ApplyTilemap();
	//MoveAlongPath(_DeltaTime);// ��ǥ�� �̻��ϰ� ���� 
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
	if (nullptr == Player) return false;

	// �÷��̾� ��ġ, ���� ���
	AttackPlayerPos = Player->GetActorLocation();
	Attackdir = AttackPlayerPos - GetActorLocation();
	AttackDistance = Attackdir.Length();
	Attackdir.Normalize();
	float speed = randomResult * _speed;
	float Gap = 300.f;

	// �浹 üũ
	bool collisionYes = Collision->CollisionCheck("Enemy", AttackPlayerPos, collisionList);
	bool isFrontMost = true; 

		// ���� �� �Ÿ� ���� �˻�
	for (UCollision* other : collisionList)
	{
		FVector otherLocation = other->GetActor()->GetActorLocation();
		float otherDistance = (otherLocation - GetActorLocation()).Length();

		// �ʹ� ������ �о
		if (otherDistance < Scale.X * 2.0f)
		{
			FVector PushDir = (GetActorLocation() - otherLocation).NormalizeReturn();
			AddActorLocation(PushDir *  speed ); // �ݴ� �������� �о
		}

		// ���� �տ� �ִ��� üũ
		float otherToPlayerDist = (AttackPlayerPos - otherLocation).Length();
		if (otherToPlayerDist < AttackDistance)
		{
			isFrontMost = false;
			break;
		}
	}
	// 2. �÷��̾�� �Ÿ� ���� �˻�
	//float PlayerRadius = Player->GetActorTransform().WorldScale.X;
	float MinDistanceToPlayer = 200.f;// *PlayerRadius; // �÷��̾�� ������ �Ÿ�
	float DistanceToPlayer = (GetActorLocation() - AttackPlayerPos).Length();

	if (DistanceToPlayer < MinDistanceToPlayer)
	{
		// �÷��̾�� �ʹ� ������ �ݴ� �������� �о
		FVector PushDir = (GetActorLocation() - AttackPlayerPos).NormalizeReturn();
		AddActorLocation(PushDir * _DeltaTime * speed * 0.5f);
	}



	// �÷��̾�� �̵� 
	if (true == isFrontMost)
	{
		if (AttackDistance > Gap){
			AddActorLocation(Attackdir * _DeltaTime * speed);
		}
		else{
			AddActorLocation(FVector::ZERO); // ����
		}
	}

	// �̵� ������ ��ü ȸ��
	if (Attackdir.Z != 0.0f || Attackdir.X != 0.0f)
	{
		float targetAngle = atan2(-Attackdir.X, Attackdir.Z) * UEngineMath::R2D;
		float currentAngle = GetActorTransform().Rotation.Y;
		float deltaAngle = targetAngle - currentAngle;
		if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
		if (deltaAngle < -180.0f) deltaAngle += 360.0f;

		// �ε巯�� ȸ��
		float lerpedAngle = currentAngle + deltaAngle * _DeltaTime * 1.0f;
		AddActorRotation(FVector(0.0f, lerpedAngle - currentAngle, 0.0f));
	}

	return true;
}

void ABzEnemyCube::AvoidWall(float _DeltaTime)
{
	FVector pos = GetActorLocation();
	float radius = 300.f;

	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());
	const std::vector<ABzTile*>& wall = GM->map->BottomTiles;

	for (ABzTile* Tile : wall)
	{
		FVector tilePos = Tile->GetActorLocation();
		float distance = (tilePos - pos).Length();

		if (true == Tile->GetWalkable() &&  distance < radius)
		{
			FVector avoidDir = (pos - tilePos).NormalizeReturn();
			SetActorRotation(FVector{0.f,60.f,0.f});
			AddActorLocation(avoidDir * _DeltaTime * 20.f);
			break;
		}
	}



}



float ABzEnemyCube::GetRandom(float _x) 
{
	float x = this->random.Randomfloat(-_x, _x);
	float y = UEngineMath::Clamp(x, 0.3f, x * 1.f);
	return y;
}

void ABzEnemyCube::ApplyTilemap()
{
	FVector pos = GetActorLocation();
	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());

	if (!GM)
	{
		return;
	}

	// Ÿ�ϸ��� �ùٸ� ������ ���
	const std::vector<ABzTile*>& BottomTiles = GM->map->BottomTiles;

	if (BottomTiles.empty())
	{
		return;
	}

	// ���� ����� Ÿ�� ã��
	ABzTile* ClosestTile = nullptr;
	float MinDistance = FLT_MAX;

	for (ABzTile* Tile : BottomTiles)
	{
		if (!Tile) continue;

		float Distance = (Tile->GetActorLocation() - pos).Length();
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestTile = Tile;
		}
	}

	if (ClosestTile)
	{
		FVector TilePos = ClosestTile->GetActorLocation();
		SetActorLocation(FVector(pos.X, TilePos.Y, pos.Z));
	}
}


void ABzEnemyCube::MoveAlongPath(float DeltaTime)
{
	if (AStarPath.empty()) return;

	FVector CurrentPos = GetActorLocation();
	FVector TargetPos = AStarPath.front();

	float Speed = 200.f;
	FVector Direction = (TargetPos - CurrentPos).NormalizeReturn();
	SetActorLocation(CurrentPos + Direction * Speed * DeltaTime);

	if ((CurrentPos - TargetPos).Length() < 10.f)
	{
		AStarPath.pop_front();
	}
}

void ABzEnemyCube::TakeDamage()
{
	UEngineDebug::OutPutString("Enemy is damaged");
}
