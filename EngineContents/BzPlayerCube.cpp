#include "PreCompile.h"
#include "BzPlayerCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include "BzProjectile.h"
#include "Skl_BzRockfall.h"


ABzPlayerCube::ABzPlayerCube()
{
	// root ������ ����Ʈ������Ʈ 
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 60.f,120.f,60.f });
	Renderer->SetPivot(PivotType::Bottom);

	RendererFront = CreateDefaultSubObject<UBzRendererDefault>();
	RendererFront->SetupAttachment(RootComponent);
	RendererFront->SetScale3D({ 25.f,25.f,100.f });
	RendererFront->SetRotation({0.f,-90.f,0.f});
	RendererFront->SetRelativeLocation({60.f,140.f,0.f});
	RendererFront->AddLocalRotation({30.f,0.f,0.f});
	
	

	FireRot = RendererFront->GetTransformRef().WorldRotation;
	//----collision
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionProfileName("Player");
	Collision->SetCollisionType(ECollisionType::OBB);

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
	{
		//_Other->GetActor()->Destroy();
		//UEngineDebug::OutPutString("Enter");
	});


#ifdef renderer_test
	//RendererBottom = CreateDefaultSubObject<UBzRendererDefault>();
	//RendererBottom->SetupAttachment(RootComponent);
	//RendererBottom->SetMesh("Rect");
	//RendererBottom->SetRelativeScale3D({ 1500.f,1500.f,1.f });
	//RendererBottom->SetRotation({ 90.f,0.f,0.f });

	// �������� �����.
	//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//LogoRenderer->SetupAttachment(RootComponent);
	//LogoRenderer->SetAutoScaleRatio(5.0f);

	//LogoRenderer->CreateAnimation("Idle", "Tevi", 0, 3, 0.5f);
	//LogoRenderer->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
	//LogoRenderer->ChangeAnimation("Move");
	//LogoRenderer->SetAutoScale(false);
#endif renderer_test

	{
		//{// ��Ʋ�󽺿��� �ִ� 
			//TestSprite->SetSprite("Player.png",2);
			//TestSprite->CreateAnimation("Idle", "Player.png", 0, 70, 0.1f);
			//TestSprite->ChangeAnimation("Idle");
		//}

		{ // ����° ��������Ʈ �ִ� 
			//TestSprite->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
			//USpriteRenderer::FrameAnimation* Animation = TestSprite->FindAnimation("Move");
			//Animation->IsAutoScale = true;
			//Animation->AutoScaleRatio = 1.0f;
			//TestSprite->ChangeAnimation("Move");
		}

		{ // ���� �̹������ 
			//TestSprite->SetTexture("BackGround.png");
			//TestSprite->SetTexture("Player_Test.png");
		}

	}
	//-------------------------------------
#ifdef TimeEventTest 
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	TimeEventComponent->AddEvent(1.f, // 1�� ����
		[this](float _Delta, float _Acc)
		{
			float yMax = GetActorTransform().Location.Y;

			if (yMax < 400.f) // �Ʒ������� ����� ��
			{
				FVector up(0.f, 250.f * _Delta, 0.f); // ���� �̵�
				AddRelativeLocation(up);
			}
			else
			{
				//Destroy(0.0f);
			}
		},
		[this]()
		{
		},
		true // �ݺ� ����
	);
#endif 
}

ABzPlayerCube::~ABzPlayerCube()
{
}

void ABzPlayerCube::BeginPlay()
{
	AActor::BeginPlay();

	Camera = GetWorld()->GetCamera(0);
	FVector thisPos = GetActorLocation();
	FVector camPos = Camera->GetActorLocation();
	diff = camPos - thisPos;
	diff += {0.f, 0.f, -1000.f};
}

void ABzPlayerCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CalculateMoveDirection(_DeltaTime);

	FVector thisPos = GetActorLocation();

	FireRot = RendererFront->GetTransformRef().Rotation;

	if (UEngineInput::IsDown('Q'))
	{
		Skl_Rockfall();
	}


	//----test
	if (UEngineInput::IsDown('F'))
	{
		GetWorld()->GetCamera(EEngineCameraType::UICamera)->SetActiveSwitch();
	}

}

FVector ABzPlayerCube::CalculateMoveDirection(float _DeltaTime)
{
	MoveDirection = FVector(0.0f, 0.0f, 0.0f);

	if (UEngineInput::IsPress('A'))
	{
		MoveDirection.X -= MoveSpeed * _DeltaTime;
	}
	if (UEngineInput::IsPress('D'))
	{
		MoveDirection.X += MoveSpeed * _DeltaTime;
	}
	if (UEngineInput::IsPress('W'))
	{
		MoveDirection.Z += MoveSpeed * _DeltaTime;
	}
	if (UEngineInput::IsPress('S'))
	{
		MoveDirection.Z -= MoveSpeed * _DeltaTime;
	}

	AddRelativeLocation(MoveDirection);

	// ȸ�� 
	if (MoveDirection.X != 0.0f || MoveDirection.Z != 0.0f)
	{
		// ��ǥ ���� ��� (Z �� ����)
		float targetAngle = atan2(-MoveDirection.Z, MoveDirection.X) * UEngineMath::R2D;
		float currentAngle = GetActorTransform().Rotation.Y;
		// ���� ���� ��� �� ���� (-180 ~ 180��)
		float deltaAngle = targetAngle - currentAngle;
		if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
		if (deltaAngle < -180.0f) deltaAngle += 360.0f;

		float lerpedAngle = currentAngle + deltaAngle * _DeltaTime * 5.0f; // ȸ�� �ӵ� ���
		AddActorRotation(FVector(0.0f, lerpedAngle - currentAngle, 0.0f));
	}

	return MoveDirection;
}

void ABzPlayerCube::Skl_Rockfall()
{
	RendererFront->SetRelativeLocation({ 30.f,220.f,0.f });
	RendererFront->AddLocalRotation({ 50.f,0.f,0.f });

	FVector pos = RendererFront->GetTransformRef().Location;
	FVector rot = RendererFront->GetTransformRef().Rotation;
	FVector MoveDir = GetActorForwardVector();

	std::shared_ptr<ASkl_BzRockfall> Proj = GetWorld()->SpawnActor<ASkl_BzRockfall>();
	//Proj->SetPlayer(PlayerCube);
	Proj->SetActorLocation(pos);
	Proj->SetActorRotation(rot);
}

