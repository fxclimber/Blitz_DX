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
#include "BzEnemyCube.h"


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

}

void ABzHomingProjectile::BeginPlay()
{
	AActor::BeginPlay();


}



void ABzHomingProjectile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CalculateMoveAcceleration(_DeltaTime);
	ForwardDir += Gravity *_DeltaTime;
	AddActorLocation(ForwardDir * _DeltaTime * Speed);
	std::string fireRotString =
		"FireRot: (X: " + std::to_string(ForwardDir.X) +
		", Y: " + std::to_string(ForwardDir.Y) +
		", Z: " + std::to_string(ForwardDir.Z) + ")";
	//UEngineDebug::OutPutString(fireRotString);

	auto Enemy = GetWorld()->GetAllActorListByClass<ABzEnemyCube>();
	
	for (auto& enemy : Enemy) {
		if (enemy) {
			UpdatePositionAndOrientation(_DeltaTime); // 원하는 함수 호출
		}
	}

}


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
	float fDeltaTime = _DeltaTime;

	//m_fLastUpdateTime = fTime;
	//if (fDeltaTime > 1.0f)
	//{
	//	return;
	//}

	FVector pos, targetdir, targetPos;
	//NiPoint3 kTrans, kTargetVector, kTargetTrans;
	pos = GetActorLocation();

	//kTrans = m_pkMissileNode->GetTranslate();

	FVector rot;
	//NiMatrix3 kTargetRot;
	FVector currentRot = GetActorTransform().Rotation;

	//NiMatrix3 kRotation = m_pkMissileNode->GetRotate();
	//NiPoint3 kHeading;

	FVector forDir = GetActorForwardVector();
	forDir.Normalize();

	//kHeading = kRotation * NiPoint3(0.f, -1.f, 0.f);
	//kHeading.Unitize();

	//if (nullptr != Enemy1)
	{
		//targetPos = Enemy->
	}


	//if (m_pkTargetObject)
	//{
	//	kTargetTrans = m_pkTargetObject->GetWorldTranslate();
	//	kTargetVector = kTargetTrans - kTrans;

	//	if (kTargetVector.Dot(kHeading) > 0.f)
	//	{
	//		float fTheta = 0.2f * fDeltaTime;
	//		NiPoint3 kAxis = kTargetVector.Cross(kHeading);
	//		kAxis.Unitize();
	//		NiMatrix3 kChangeRot;
	//		kChangeRot.MakeRotation(fTheta, kAxis);
	//		kRotation = kChangeRot * kRotation;
	//		m_pkMissileNode->SetRotate(kRotation);
	//		kHeading = kRotation * NiPoint3(0.f, -1.f, 0.f);
	//		kHeading.Unitize();
	//	}
	//}
	//kHeading = MISSILE_SPEED * fDeltaTime * kHeading;
	//m_pkMissileNode->SetTranslate(kHeading + kTrans);
}