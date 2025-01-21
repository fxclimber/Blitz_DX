#include "PreCompile.h"
#include "BzHomingProjectile.h"

#include <EngineCore/Collision.h>
#include "BzPlayerCube.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineBase/EngineMath.h>
#include <algorithm>

#include "BzEnemyCube.h"
#include "BzPlayerCube.h"
#include "BzGameMode_Intro.h"
#include "BzClassManager.h"

#include <DirectXMath.h>
using namespace DirectX;

ABzHomingProjectile::ABzHomingProjectile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
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
			//UEngineDebug::OutPutString("Enter");
		});

	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());
	Manager = GM->Manager;

}

void ABzHomingProjectile::BeginPlay()
{
	AActor::BeginPlay();
	Player = dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());
	TargetEnemy = SetTargetEnemy();


}



void ABzHomingProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//UpdatePositionAndOrientation(_DeltaTime);

	//CalculateMoveAcceleration(_DeltaTime);
	//ForwardDir += Gravity *_DeltaTime;
	//AddActorLocation(ForwardDir * _DeltaTime * Speed);

	{
		std::string fireRotString =
			"FireRot: (X: " + std::to_string(ForwardDir.X) +
			", Y: " + std::to_string(ForwardDir.Y) +
			", Z: " + std::to_string(ForwardDir.Z) + ")";
		//UEngineDebug::OutPutString(fireRotString);
	}


}

// 사용안하는중
FVector ABzHomingProjectile::CalculateMoveAcceleration(float _DeltaTime)
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

void ABzHomingProjectile::SetPlayer(class ABzPlayerCube* _name)
{
	Player = _name;
}


void ABzHomingProjectile::UpdatePositionAndOrientation(float _DeltaTime)
{
	float turnRate = 120.0f;
	float speed = 100.f;
	FVector targetPos = TargetEnemy->GetActorLocation();
	FVector projPos = GetActorLocation();
		
		// 목표까지의 방향 벡터 계산
		FVector toTarget = (targetPos - projPos).NormalizeReturn();//타겟벡터
		FVector direction = GetActorForwardVector().NormalizeReturn();//전방벡터
		float dotProduct = UEngineMath::Clamp(FVector::Dot(direction, toTarget),-1.0f,1.0f);
		// 회전 각도 계산
		float angleToTarget = acosf(dotProduct);
		float turnAngle = UEngineMath::ClampMax((turnRate * _DeltaTime), angleToTarget);

		// 회전 축 계산 (현재 방향과 목표 방향의 외적)
		FVector rotationAxis = (FVector::Cross(direction, toTarget)).NormalizeReturn();

		// 이동방향으로 회전시키는 공식인데, dx함수와 현재엔진함수 못섞겠어...
		//XMVECTOR rotationQuat = XMQuaternionRotationAxis(XMLoadFloat3(&rotationAxis), turnAngle);
		//direction = rotationQuat.RotateVector(direction);//?
		//direction.Normalize();

		projPos = direction * speed * _DeltaTime;
		//SetActorLocation(projPos);
		//AddActorRotation(rotationAxis* turnAngle);

		FVector Attackdir = toTarget;
		//AddActorLocation(projPos * _DeltaTime * speed);



}

ABzEnemyCube* ABzHomingProjectile::SetTargetEnemy()
{
	// 매니저를 만들었는데 엔진에 기능있었네 
	//auto Enemy = GetWorld()->GetAllActorListByClass<ABzEnemyCube>();

	auto& enemyList = Manager->Enemies;

	if (enemyList.empty()) return nullptr; // 적이 없으면 nullptr 반환

	static size_t currentIndex = 0; // 현재 선택된 적의 인덱스

	// 현재 인덱스의 적 선택
	ABzEnemyCube* selectedEnemy = enemyList[currentIndex];

	// 다음 선택을 위해 인덱스 증가 (순환 구조)
	currentIndex = (currentIndex + 1) % enemyList.size();

	return selectedEnemy;
}

