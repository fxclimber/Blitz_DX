#include "PreCompile.h"
#include "BzPlayerCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>
#include "BzProjectile.h"
#include "Skl_BzRockfall.h"
#include "BzMissile.h"
#include "BzArcStone.h"

#include "BzGameMode_Intro.h"
#include "BzTileMap.h"



ABzPlayerCube::ABzPlayerCube()
{
	// root 역할의 디폴트컴포넌트 
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 80.f,130.f,100.f });
	Renderer->SetPivot(PivotType::Bottom);

	RendererFront = CreateDefaultSubObject<UBzRendererDefault>().get();
	RendererFront->SetupAttachment(RootComponent);
	RendererFront->SetScale3D({ 25.f,25.f,100.f });
	RendererFront->SetRotation({30.f,-90.f,0.f});
	RendererFront->SetRelativeLocation({80.f,140.f,0.f});

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

	Skl_RockfallOn = false;
	OrgScale = GetActorTransform().Scale;


#ifdef renderer_test
	//RendererBottom = CreateDefaultSubObject<UBzRendererDefault>();
	//RendererBottom->SetupAttachment(RootComponent);
	//RendererBottom->SetMesh("Rect");
	//RendererBottom->SetRelativeScale3D({ 1500.f,1500.f,1.f });
	//RendererBottom->SetRotation({ 90.f,0.f,0.f });

	// 랜더러를 만든다.
	//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//LogoRenderer->SetupAttachment(RootComponent);
	//LogoRenderer->SetAutoScaleRatio(5.0f);

	//LogoRenderer->CreateAnimation("Idle", "Tevi", 0, 3, 0.5f);
	//LogoRenderer->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
	//LogoRenderer->ChangeAnimation("Move");
	//LogoRenderer->SetAutoScale(false);
#endif renderer_test

	{
		//{// 아틀라스에서 애니 
			//TestSprite->SetSprite("Player.png",2);
			//TestSprite->CreateAnimation("Idle", "Player.png", 0, 70, 0.1f);
			//TestSprite->ChangeAnimation("Idle");
		//}

		{ // 폴더째 스프라이트 애니 
			//TestSprite->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
			//USpriteRenderer::FrameAnimation* Animation = TestSprite->FindAnimation("Move");
			//Animation->IsAutoScale = true;
			//Animation->AutoScaleRatio = 1.0f;
			//TestSprite->ChangeAnimation("Move");
		}

		{ // 낱장 이미지사용 
			//TestSprite->SetTexture("BackGround.png");
			//TestSprite->SetTexture("Player_Test.png");
		}

	}
	//-------------------------------------
#ifdef TimeEventTest 
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	TimeEventComponent->AddEvent(1.f, // 1초 간격
		[this](float _Delta, float _Acc)
		{
			float yMax = GetActorTransform().Location.Y;

			if (yMax < 400.f) // 아래쪽으로 벗어났을 때
			{
				FVector up(0.f, 250.f * _Delta, 0.f); // 위로 이동
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
		true // 반복 실행
	);
#endif 
}

ABzPlayerCube::~ABzPlayerCube()
{
}

void ABzPlayerCube::BeginPlay()
{
	AActor::BeginPlay();

	// cam setting 
	Camera = GetWorld()->GetCamera(0).get();
	Camera->GetCameraComponent()->SetFOV(fov);
	FVector thisPos = GetActorLocation();
	FVector camPos = Camera->GetActorLocation();
	diff = camPos - thisPos;
	diff += {0.f, 0.f, -1000.f};
}

void ABzPlayerCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	UEngineCamera* CameraP = Camera->GetCameraComponent().get();

	//-----------------kEY Dash 
	if (UEngineInput::IsPress('F'))
	{
		IsDash = true;
		DashTime = 0.0f; 
	}

	if (!IsDash)
	{
		CalculateMoveDirection(_DeltaTime);
	}
	else
	{
		DashTime += _DeltaTime; 

		if (DashTime > 15.0f)
		{
			IsDash = false; 
		}
		else
		{
			CalculateMoveDirection(_DeltaTime);
			Skl_Dash(MoveDirection, 5.f, _DeltaTime);
		}
	}

	// Key - Attack 
	if (UEngineInput::IsDown('L'))
	{
		Skl_Rockfall();//다시해야함 
	}

	if (UEngineInput::IsDown('K'))
	{
		Skl_Missile();
	}
	if (UEngineInput::IsDown('J'))
	{
		Skl_ArcStone();
	}
	if (UEngineInput::IsPress('F'))
	{
		IsDash = true;
	}
	if (UEngineInput::IsDown('G'))
	{
		Atk();
	}




	//----test
	if (UEngineInput::IsPress('E'))
	{
		AddActorRotation(FVector{0.f,1.f,0.f});
	}
	//if (UEngineInput::IsDown('F'))
	//{
	//	GetWorld()->GetCamera(EEngineCameraType::UICamera)->SetActiveSwitch();
	//}


	//------------지형높이따라 y값조절 테스트 
	ApplyTilemap();

	if (UEngineInput::IsDown(VK_SPACE))
	{
	}

	// zoom 
	if (UEngineWindow::GetWheelDir() != 0)
	{
		fov -= UEngineWindow::GetWheelDir() * 0.05f; // 조절 속도
		Camera->GetCameraComponent()->SetFOV(fov);
		UEngineDebug::OutPutString(std::to_string(fov));
		UEngineWindow::SetWheelDir();
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

	// 회전 
	if (MoveDirection.X != 0.0f || MoveDirection.Z != 0.0f)
	{
		// 목표 각도 계산 (Z 축 반전)
		float targetAngle = atan2(-MoveDirection.Z, MoveDirection.X) * UEngineMath::R2D;
		float currentAngle = GetActorTransform().Rotation.Y;
		// 각도 차이 계산 및 보정 (-180 ~ 180도)
		float deltaAngle = targetAngle - currentAngle;
		if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
		if (deltaAngle < -180.0f) deltaAngle += 360.0f;

		float lerpedAngle = currentAngle + deltaAngle * _DeltaTime * 5.0f; // 회전 속도 계수
		AddActorRotation(FVector(0.0f, lerpedAngle - currentAngle, 0.0f));
	}

	return MoveDirection;
}


void ABzPlayerCube::Skl_Rockfall()
{
	FVector OriginalLocation = RendererFront->GetRelativeLocation();
	FVector OriginalRotation = RendererFront->GetTransformRef().Rotation;

	if (false == Skl_RockfallOn)
	{
		RendererFront->SetRelativeLocation({ 30.f, 220.f, 0.f });
		RendererFront->AddLocalRotation({ 50.f, 0.f, 0.f });

		FVector pos = RendererFront->GetTransformRef().Location;
		FVector rot = RendererFront->GetTransformRef().Rotation;
		FVector MoveDir = GetActorForwardVector();

		std::shared_ptr<ASkl_BzRockfall> Proj = GetWorld()->SpawnActor<ASkl_BzRockfall>();
		Proj->SetActorLocation(pos);
		Proj->SetActorRotation(rot);
		Skl_RockfallOn = true;
	}

	if (true == Skl_RockfallOn)
	{
		RendererFront->SetRotation({ 30.f, -90.f, 0.f });
		RendererFront->SetRelativeLocation({ 60.f, 140.f, 0.f });
		Skl_RockfallOn = false;
	}

	// 원래 위치와 회전으로 복원
	RendererFront->SetRelativeLocation(OriginalLocation);
	RendererFront->SetRotation(OriginalRotation);
}

void ABzPlayerCube::Skl_ArcStone()
{
	std::shared_ptr<ABzArcStone> Proj = GetWorld()->SpawnActor<ABzArcStone>();
	Proj->SetPlayer(this);
	//Proj->SetActorLocation(GetActorLocation());
	//Proj->SetActorLocation({});
}

void ABzPlayerCube::Skl_Missile()
{
	std::shared_ptr<ABzMissile> Proj = GetWorld()->SpawnActor<ABzMissile>();
	Proj->SetPlayer(this);
	Proj->SetActorLocation(GetActorLocation());

}

void ABzPlayerCube::ApplyTilemap()
{
	FVector pos = GetActorLocation();
	ABzGameMode_Intro* GM = dynamic_cast<ABzGameMode_Intro*>(GetWorld()->GetGameMode());

	if (!GM)
	{
		return;
	}

	// 타일맵의 올바른 변수명 사용
	const std::vector<ABzTile*>& BottomTiles = GM->map->BottomTiles;

	if (BottomTiles.empty())
	{
		return;
	}

	// 가장 가까운 타일 찾기
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


void ABzPlayerCube::Skl_Dash(FVector _Direction, float _Speed, float _DeltaTime)
{
	static float Time = 0.0f;
	Time += _DeltaTime;
	const float BaseAmplitude = 0.1f;
	const float Frequency = 2.0f;
	const float ScaleFactor = 0.9f;
	const float RotationFactor = 0.05f;
	const float Speed = _Speed;
	const float Acceleration = 0.2f;

	float dynamicspeed = Speed + Acceleration * Time;
	float dirLength = _Direction.NormalizeReturn().Length() * dynamicspeed;

	float Amplitude = BaseAmplitude * Speed;
	FVector Offset = _Direction * (Amplitude * dirLength * fabs(sin(Frequency * Time)));
	Offset.ABSVectorReturn();
	AddActorLocation(Offset);

	FVector TargetScale = FVector(UEngineMath::Clamp((OrgScale.X + OrgScale.X * dirLength), 0.9f, 1.0f), OrgScale.Y, OrgScale.Z);

	if (1.0f <= dirLength)
	{
		AddActorScale3D({ TargetScale.X * 0.01f,0.f,0.f });
	}
	else
	{
		SetActorRelativeScale3D(OrgScale);
	}
	
}

void ABzPlayerCube::Atk()
{
	std::shared_ptr<ABzProjectile> Proj = GetWorld()->SpawnActor<ABzProjectile>();
	Proj->SetPlayer(this);
	Proj->SetActorLocation(GetActorLocation());
}

