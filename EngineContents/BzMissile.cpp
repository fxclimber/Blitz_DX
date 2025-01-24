#include "PreCompile.h"
#include "BzMissile.h"
#include <EngineCore/Collision.h>
#include "BzPlayerCube.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineBase/EngineMath.h>

#include "BzEnemyCube.h"
#include "BzPlayerCube.h"
#include "BzGameMode_Intro.h"
#include "BzClassManager.h"

#include <DirectXMath.h>
using namespace DirectX;

ABzMissile::ABzMissile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	//Renderer->SetScale3D({ 10.f,10.f,55.f });
	Renderer->SetScale3D({ 35.f,35.f,85.f });
	Renderer->GetRenderUnit().SetTexture("bz_texture0", "bulletTest.jpg");

	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionProfileName("Proj");
	Collision->SetCollisionType(ECollisionType::OBB);

}

void ABzMissile::BeginPlay()
{
	AActor::BeginPlay();

	Player = dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());

	{
		MoveDirection = Player->GetActorTransform().GetLocalFoward();

		auto fire = Player->GetFire();
		const auto& pos = fire->GetTransformRef().WorldLocation;
		const auto& scale = fire->GetTransformRef().WorldScale;
		const auto& rotRender = fire->GetTransformRef().Rotation;
		FVector rot = Player->GetActorTransform().Rotation;
		//rot -= rotRender;

		FVector SpawnPos = FVector(pos.X, pos.Y, pos.Z);
		FVector SpawnScale = FVector(scale.X, scale.Y, scale.Z);

		fire->GetTransformRef().Location;
		SetActorLocation(SpawnPos);
		ForwardDir = GetActorForwardVector();
	}
	TargetEnemy = FindTarget();
}



void ABzMissile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	MoveDirection = GetActorForwardVector();


	if (nullptr == TargetEnemy)
	{
		return;
	}
	else
	{
		TargetEnemy = FindTarget();
		ComputeHomingRotation(_DeltaTime);
	}

	


}


FVector ABzMissile::CalculateMoveAcceleration(float _DeltaTime)
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

		// 새로운 회전값 설정
		FVector newRotation(lerpedPitch, lerpedYaw, currentRotation.Z); // Roll 고정
		SetActorRotation(newRotation);
	}
	
	return ForwardDir;
}

void ABzMissile::Differenciate(ABzClassManager& manager)
{
	if (false != bActive)
	{
		return;
	}

	Pos = GetActorLocation();
	ABzEnemyCube* target = manager.GetClosestEnemy(Pos);

	if (target && IsColliding(target))
	{
		target->TakeDamage();
		manager.RemoveEnemy(target);
		bActive = false;
	}
}

bool ABzMissile::IsColliding(ABzEnemy* enemy)
{
	return (Pos - enemy->GetActorLocation()).Length() < 3.f;
}

void ABzMissile::SetPlayer(class ABzPlayerCube* _name)
{
	Player = _name;
}




ABzEnemyCube* ABzMissile::FindTarget()
{
	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());
	std::vector<class ABzEnemyCube*> enemiesList = GM->GetEnemyCubesList();
	return enemiesList[0];
}


void ABzMissile::ComputeHomingRotation(float DeltaTime)
{
	{

		FVector TargetPosF = TargetEnemy->GetActorLocation();
		TargetPosF += {0.f, 200.f, 0.f};
		FVector  TargetDirF = (TargetPosF - GetActorLocation()).NormalizeReturn();
		FVector move = TargetDirF * DeltaTime * 400.f;
		AddActorLocation(move);

	// 방향 벡터 정규화
	FVector currentDir = GetActorForwardVector();
	FVector targetDir = TargetEnemy->GetActorLocation() - GetActorLocation();
	float RotationSpeed = 5500.f;

	XMVECTOR CurrentDir = XMVector3Normalize(currentDir.DirectVector);
	XMVECTOR TargetDir = XMVector3Normalize(targetDir.DirectVector);
	// 회전 축 계산 (Cross Product)
	XMVECTOR RotationAxis = XMVector3Cross(CurrentDir, TargetDir);
	float Dot = XMVectorGetX(XMVector3Dot(CurrentDir, TargetDir));

	// 안정화 (각도 범위 보정)
	Dot = max(-1.0f, min(1.0f, Dot));

	float Angle = acosf(Dot);
	float RotateAmount = RotationSpeed * DeltaTime;
	//Angle = min(Angle, RotateAmount); // 한 번에 너무 많이 돌지 않도록 제한
	Angle *= RotateAmount;
	// 회전 적용 (Axis-Angle 회전)
	XMVECTOR NewDir = XMVector3TransformNormal(CurrentDir, XMMatrixRotationAxis(TargetDir, Angle));
	FVector Result;
	XMStoreFloat3(&Result.DirectFloat3, NewDir);

	AddActorRotation(Result);

}

	{
		// 그냥 z로컬로만 회전
		//if (!TargetEnemy) return;

		//// 현재 위치 및 목표 방향 계산
		//FVector TargetPos = TargetEnemy->GetActorLocation();
		//FVector MoveDirection = (TargetPos - GetActorLocation()).NormalizeReturn();

		//// 현재 방향 벡터 가져오기
		//FVector CurrentDir = GetActorForwardVector();

		//// 목표 방향과 현재 방향의 Yaw 각도 계산
		//float targetAngle = atan2(-MoveDirection.Y, MoveDirection.X) * UEngineMath::R2D;
		//float currentAngle = atan2(-CurrentDir.Y, CurrentDir.X) * UEngineMath::R2D;

		//// 각도 차이 계산 및 보정 (-180 ~ 180도)
		//float deltaAngle = targetAngle - currentAngle;
		//if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
		//if (deltaAngle < -180.0f) deltaAngle += 360.0f;

		//// 회전 속도 조절
		//float RotationSpeed = 20.f;
		//float RotationAmountZ = deltaAngle * DeltaTime * RotationSpeed;

		//// 로컬 Z축 회전 적용
		//AddActorRotation(FVector(0.0f, 0.0f, RotationAmountZ));

		//// 이동 적용
		//FVector move = MoveDirection * DeltaTime * 100.f;
		//AddActorLocation(move);

	}

}


void ABzMissile::KillEnemy()
{
	std::vector<UCollision*> col;
	if (true == Collision->CollisionCheck("Enemy", col))
	{
		col[0]->GetActor()->Destroy();
		Destroy();
	}
}
