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


ABzMissile::ABzMissile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 10.f,10.f,55.f });
	//Renderer->SetScale3D({ 35.f,35.f,85.f });
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
		MoveDirection = Player->GetActorTransform().Rotation;

		auto fire = Player->GetFire();
		const auto& pos = fire->GetTransformRef().WorldLocation;
		const auto& scale = fire->GetTransformRef().WorldScale;
		const auto& rotRender = fire->GetTransformRef().Rotation;
		FVector rot = Player->GetActorTransform().Rotation;
		rot -= rotRender;


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
	UpdatePositionAndOrientation(_DeltaTime);


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
	// 매니저를 만들었는데 엔진에 기능있었네 
	//auto enemyList = GetWorld()->GetAllActorListByClass<ABzEnemyCube>();

	if (!this) return nullptr; // this가 nullptr이면 함수 종료
	if (!Manager) return nullptr; // Manager가 nullptr이면 함수 종료

	auto& enemyList = Manager->Enemies;
	if (enemyList.empty()) return nullptr; // 적이 없으면 nullptr 반환

	static size_t currentIndex = 0; // 현재 선택된 적의 인덱스

	// 현재 인덱스가 유효한지 확인
	if (currentIndex >= enemyList.size()) {
		currentIndex = 0; // 범위를 벗어나면 처음부터 다시 시작
	}

	// NULL이 아닌 유효한 적을 찾을 때까지 반복
	size_t startIndex = currentIndex; // 시작 위치 저장
	ABzEnemyCube* selectedEnemy = nullptr;

	do {
		selectedEnemy = enemyList[currentIndex];
		currentIndex = (currentIndex + 1) % enemyList.size(); // 다음 인덱스로 이동
	} while (!selectedEnemy && currentIndex != startIndex);

	return selectedEnemy; // 유효한 적 반환 (없으면 nullptr)
}
