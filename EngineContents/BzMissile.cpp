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
			SetActorLocation(pos);// ����- Y ��ġ ����
		}
	}
	if (!(ForwardDir.X == 0.0f && ForwardDir.Y == 0.0f && ForwardDir.Z == 0.0f))
	{
		FVector normalizedDir = ForwardDir.NormalizeReturn();

		float targetYaw = atan2(normalizedDir.X, normalizedDir.Z); // XZ ��� ����
		float targetPitch = atan2(normalizedDir.Y, sqrt(normalizedDir.X * normalizedDir.X + normalizedDir.Z * normalizedDir.Z)); // Y�� ����

		FVector currentRotation = GetActorTransform().Rotation;

		float deltaYaw = targetYaw - currentRotation.Y;
		float deltaPitch = targetPitch - currentRotation.X;

		if (deltaYaw > DirectX::XM_PI) deltaYaw -= DirectX::XM_2PI;
		if (deltaYaw < -DirectX::XM_PI) deltaYaw += DirectX::XM_2PI;

		if (deltaPitch > DirectX::XM_PI) deltaPitch -= DirectX::XM_2PI;
		if (deltaPitch < -DirectX::XM_PI) deltaPitch += DirectX::XM_2PI;

		float lerpedYaw = currentRotation.Y + deltaYaw * _DeltaTime * 3.0f; // �ӵ� ��� 3.0f
		float lerpedPitch = currentRotation.X + deltaPitch * _DeltaTime * 103.0f;

		// ���ο� ȸ���� ����
		FVector newRotation(lerpedPitch, lerpedYaw, currentRotation.Z); // Roll ����
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

	// ���� ���� ����ȭ
	FVector currentDir = GetActorForwardVector();
	FVector targetDir = TargetEnemy->GetActorLocation() - GetActorLocation();
	float RotationSpeed = 5500.f;

	XMVECTOR CurrentDir = XMVector3Normalize(currentDir.DirectVector);
	XMVECTOR TargetDir = XMVector3Normalize(targetDir.DirectVector);
	// ȸ�� �� ��� (Cross Product)
	XMVECTOR RotationAxis = XMVector3Cross(CurrentDir, TargetDir);
	float Dot = XMVectorGetX(XMVector3Dot(CurrentDir, TargetDir));

	// ����ȭ (���� ���� ����)
	Dot = max(-1.0f, min(1.0f, Dot));

	float Angle = acosf(Dot);
	float RotateAmount = RotationSpeed * DeltaTime;
	//Angle = min(Angle, RotateAmount); // �� ���� �ʹ� ���� ���� �ʵ��� ����
	Angle *= RotateAmount;
	// ȸ�� ���� (Axis-Angle ȸ��)
	XMVECTOR NewDir = XMVector3TransformNormal(CurrentDir, XMMatrixRotationAxis(TargetDir, Angle));
	FVector Result;
	XMStoreFloat3(&Result.DirectFloat3, NewDir);

	AddActorRotation(Result);

}

	{
		// �׳� z���÷θ� ȸ��
		//if (!TargetEnemy) return;

		//// ���� ��ġ �� ��ǥ ���� ���
		//FVector TargetPos = TargetEnemy->GetActorLocation();
		//FVector MoveDirection = (TargetPos - GetActorLocation()).NormalizeReturn();

		//// ���� ���� ���� ��������
		//FVector CurrentDir = GetActorForwardVector();

		//// ��ǥ ����� ���� ������ Yaw ���� ���
		//float targetAngle = atan2(-MoveDirection.Y, MoveDirection.X) * UEngineMath::R2D;
		//float currentAngle = atan2(-CurrentDir.Y, CurrentDir.X) * UEngineMath::R2D;

		//// ���� ���� ��� �� ���� (-180 ~ 180��)
		//float deltaAngle = targetAngle - currentAngle;
		//if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
		//if (deltaAngle < -180.0f) deltaAngle += 360.0f;

		//// ȸ�� �ӵ� ����
		//float RotationSpeed = 20.f;
		//float RotationAmountZ = deltaAngle * DeltaTime * RotationSpeed;

		//// ���� Z�� ȸ�� ����
		//AddActorRotation(FVector(0.0f, 0.0f, RotationAmountZ));

		//// �̵� ����
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
