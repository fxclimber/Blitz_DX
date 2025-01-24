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


	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			_Other->GetActor()->Destroy();
			_This->Destroy();
		});

	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());
	Manager = GM->Manager;

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
		SetActorRotation(rot);
		SetActorLocation(SpawnPos);
		ForwardDir = GetActorForwardVector();

	}
	//Velocity = ForwardDir * Speed;
}



void ABzMissile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//CalculateMoveAcceleration(_DeltaTime);
	//AddActorLocation(ForwardDir * _DeltaTime * Speed);
	//------------
	TargetEnemy = SetTargetEnemy();
	//UpdatePositionAndOrientation(_DeltaTime);

	float RotationSpeed = 500.f;
	

	XMVECTOR Velocity = GetActorForwardVector().NormalizeReturn().DirectVector;
	XMVECTOR ProjectilePos = GetActorLocation().DirectVector;
	//XMVECTOR TargetPos = Player->GetActorLocation().DirectVector;
	XMVECTOR TargetPos =FVector(0.f,1300.f,0.f).DirectVector;

	XMVECTOR CurrentDir = XMVector3Normalize(Velocity);
	XMVECTOR TargetDir = XMVectorSubtract(TargetPos, ProjectilePos);
	TargetDir = XMVector3Normalize(TargetDir);
	FVector HomingRotation = ComputeHomingRotation(CurrentDir, TargetDir, RotationSpeed, _DeltaTime);

	//FVector TargetPosF = Player->GetActorLocation();
	FVector TargetPosF = FVector(0.f, 1300.f, 0.f);
	FVector  TargetDirF = (TargetPosF - GetActorLocation()).NormalizeReturn();
	FVector move = TargetDirF * _DeltaTime * RotationSpeed;
	AddActorLocation(move);
	AddActorRotation(HomingRotation);

	if (TargetPosF == GetActorLocation())
	{
		AddActorLocation(FVector::ZERO);
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


void ABzMissile::UpdatePositionAndOrientation(float _DeltaTime)
{
	float turnRate = 120.0f;
	float speed = 400.f;
	if (nullptr != TargetEnemy)
	{
		FVector targetPos = TargetEnemy->GetActorLocation();
		FVector projPos = GetActorLocation();
		// 목표까지의 방향 벡터 계산
		FVector toTarget = (targetPos - projPos).NormalizeReturn();//타겟벡터
		FVector direction = GetActorForwardVector().NormalizeReturn();//전방벡터
		float dotProduct = UEngineMath::Clamp(FVector::Dot(direction, toTarget), -1.0f, 1.0f);
		// 회전 각도 계산
		float angleToTarget = acosf(dotProduct);
		float turnAngle = UEngineMath::ClampMax((turnRate * _DeltaTime), angleToTarget);
		// 회전 축 계산 (현재 방향과 목표 방향의 외적)
		FVector rotationAxis = (FVector::Cross(direction, toTarget)).NormalizeReturn();

		projPos = direction * speed * _DeltaTime;
		AddActorLocation(projPos);
		AddActorRotation(rotationAxis* turnAngle);
	}

}

ABzEnemyCube* ABzMissile::SetTargetEnemy()
{
	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());
	std::vector<class ABzEnemyCube*> list = GM->GetEnemyCubesList();

	size_t size = list.size();
	if (0 != size)
	{
		return list[0];
	}
}

//XMMATRIX ABzMissile::ComputeHomingRotation(XMVECTOR CurrentDir, XMVECTOR TargetDir, float RotationSpeed, float DeltaTime)
//{
//	// 벡터 정규화
//	//CurrentDir = XMVector3Normalize(CurrentDir);
//	//TargetDir = XMVector3Normalize(TargetDir);
//
//	// 회전 축 계산 (Cross Product)
//	XMVECTOR RotationAxis = XMVector3Cross(CurrentDir, TargetDir);
//	float Dot = XMVectorGetX(XMVector3Dot(CurrentDir, TargetDir));
//
//	// 클램핑하여 안정화
//	Dot = max(-1.0f, min(1.0f, Dot));
//
//	// 두 벡터 사이의 회전 각도 (Arc Cosine)
//	float Angle = acosf(Dot);
//	Angle *= RotationSpeed * DeltaTime; // 회전 속도 조절
//
//	// 회전 Quaternion 생성
//	XMVECTOR RotationQuat = XMQuaternionRotationAxis(RotationAxis, Angle);
//
//	// 회전 행렬 반환
//	return XMMatrixRotationQuaternion(RotationQuat);
//}


FVector ABzMissile::ComputeHomingRotation(XMVECTOR CurrentDir, XMVECTOR TargetDir, float RotationSpeed, float DeltaTime)
{
	// 벡터 정규화
	CurrentDir = XMVector3Normalize(CurrentDir);
	TargetDir = XMVector3Normalize(TargetDir);

	// 회전 축 계산 (Cross Product)
	XMVECTOR RotationAxis = XMVector3Cross(CurrentDir, TargetDir);
	float Dot = XMVectorGetX(XMVector3Dot(CurrentDir, TargetDir));

	// 안정화
	Dot = max(-1.0f, min(1.0f, Dot));

	// 두 벡터 사이의 회전 각도
	float Angle = acosf(Dot);
	Angle *= RotationSpeed * DeltaTime; // 회전 속도 적용

	// 회전 Quaternion 생성
	XMVECTOR RotationQuat = XMQuaternionRotationAxis(RotationAxis, Angle);

	// 회전 적용된 벡터 반환
	XMVECTOR NewDir = XMVector3Rotate(CurrentDir, RotationQuat);

	// XMVECTOR → FVector 변환
	FVector Result;
	XMStoreFloat3(&Result.DirectFloat3, NewDir);

	return Result;
}
