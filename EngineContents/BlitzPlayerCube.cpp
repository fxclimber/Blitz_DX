#include "PreCompile.h"
#include "BlitzPlayerCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "MyRenderer.h"

ABlitzPlayerCube::ABlitzPlayerCube()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 스프라이트 렌더러 함수들 샘플 
	TestSprite = CreateDefaultSubObject<USpriteRenderer>();
	TestSprite->SetupAttachment(RootComponent);

	//TestSprite->SetRelativeScale3D({ 250, 250, 1.0f });
	TestSprite->SetScale3D({300.f,300.f,1.f});

	{
		//{// 아틀라스에서 애니 
			TestSprite->SetSprite("Player.png",2);
			TestSprite->CreateAnimation("Idle", "Player.png", 0, 70, 0.1f);
			TestSprite->ChangeAnimation("Idle");
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


	{
		//TestSpriteChild = CreateDefaultSubObject<USpriteRenderer>();
		//TestSpriteChild->SetSprite("Player.png", 2);
		//TestSpriteChild->SetRelativeLocation({100.0f, 0.0f, 0.0f});
		//TestSpriteChild->SetScale3D({ 50.0f, 50.0f, 1.0f });
		//// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
		//TestSpriteChild->SetupAttachment(RootComponent);
	}

}

ABlitzPlayerCube::~ABlitzPlayerCube()
{
}

void ABlitzPlayerCube::BeginPlay()
{
	AActor::BeginPlay();
}

void ABlitzPlayerCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineDebug::OutPutString(Camera->ScreenMousePosToWorldPos().ToString());


	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	FVector Test = GetActorForwardVector();

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	TestSprite->AddUVPlusValue({ _DeltaTime, 0.0f, 0.0f, 1.0f });

	if (UEngineInput::IsPress('E'))
	{
		TestSprite->ChangeAnimation("Move");
		// 단 1순간만 처리되는 걸로 
		// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	}

	if (UEngineInput::IsPress('R'))
	{
		// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}