#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "MyRenderer.h"

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 랜더러를 만든다.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	// LogoRenderer->SetSprite("Player.png");
	LogoRenderer->SetTexture("BackGround.png");

	//LogoRenderer->CreateAnimation("Idle", "Tevi", 0, 3, 0.5f);
	//{
	//	USpriteRenderer::FrameAnimation* Animation = LogoRenderer->FindAnimation("Idle");
	//	Animation->IsAutoScale = true;
	//	Animation->AutoScaleRatio = 1.0f;
	//}

	//LogoRenderer->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);

	//{
	//	USpriteRenderer::FrameAnimation* Animation = LogoRenderer->FindAnimation("Move");
	//	Animation->IsAutoScale = true;
	//	Animation->AutoScaleRatio = 1.0f;
	//}

	//LogoRenderer->ChangeAnimation("Idle");

	// 부모가 존재하지 않는 root는 Relative든 Local이던 
	// 결과는 같다. 
	// 부모의 크기에 내가 영향을 받을수 있기 대문에 함수가 나뉜것이다.
	// 부모가 없으면


	// 0.1,            1.1

	LogoRenderer->SetRelativeScale3D({ 5000, 5000, 1.0f });
	LogoRenderer->SetupAttachment(RootComponent);



	//Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("Player.png", 2);
	//// 부모의 스케일이 나에게 영향을 주면서 나는 100이 아닐수가 있다
	//Child->SetRelativeLocation({100.0f, 0.0f, 0.0f});
	//Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//Child->SetupAttachment(RootComponent);
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleLogo::Tick(float _DeltaTime)
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

	LogoRenderer->AddUVPlusValue({ _DeltaTime, 0.0f, 0.0f, 1.0f });

	if (UEngineInput::IsPress('E'))
	{
		LogoRenderer->ChangeAnimation("Move");
		// 단 1순간만 처리되는 걸로 
		// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	}

	if (UEngineInput::IsPress('R'))
	{
		// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}