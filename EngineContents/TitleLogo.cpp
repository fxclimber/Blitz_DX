#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "MyCustomRenderer.h"

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;



	// 여러분들만의 랜더링을 하고 싶다면 2가지 방법이 있습니다.

	Renderer = CreateDefaultSubObject<MyCustomRenderer>();
	Renderer->SetupAttachment(RootComponent);

	// Renderer->SetMesh("Box");


	Renderer->SetRelativeScale3D({ 100.0f, 100.0f, 100.0f });


	// 랜더러를 만든다.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetupAttachment(RootComponent);
	LogoRenderer->SetAutoScaleRatio(5.0f);

	LogoRenderer->CreateAnimation("Idle", "Tevi", 0, 3, 0.5f);
	LogoRenderer->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
	LogoRenderer->ChangeAnimation("Move");
	// LogoRenderer->SetAutoScale(false);

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

	UEngineCore::GetMainWindow().GetMousePos();

	// UEngineDebug::OutPutString(Camera->ScreenMousePosToWorldPos().ToString());


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

	// LogoRenderer->AddUVPlusValue({_DeltaTime, 0.0f, 0.0f, 1.0f});

	if (UEngineInput::IsPress('F'))
	{
		LogoRenderer->ColorData.MulColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	if (UEngineInput::IsPress('E'))
	{
		LogoRenderer->ColorData.PlusColor += float4(1.0f, 1.0f, 1.0f, 1.0f) * _DeltaTime;
		LogoRenderer->ColorData.PlusColor.W += _DeltaTime;

		// LogoRenderer->ChangeAnimation("Move");
		// 단 1순간만 처리되는 걸로 
		// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	}

	if (UEngineInput::IsPress('R'))
	{
		LogoRenderer->ColorData.PlusColor -= float4(1.0f, 1.0f, 1.0f, 1.0f) * _DeltaTime;
		LogoRenderer->ColorData.PlusColor.W -= _DeltaTime;

		// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}