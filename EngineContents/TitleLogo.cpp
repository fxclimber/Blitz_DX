#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

ATitleLogo::ATitleLogo()
{
	// 랜더러를 만든다.
	//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//LogoRenderer->SetSprite("Player.png", 0);
	//LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	//RootComponent = LogoRenderer;

	//std::shared_ptr<class USpriteRenderer> Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("Player.png", 2);
	//Child->SetLocation({ 2.0f, 0.0f, 0.0f });
	//Child->SetupAttachment(RootComponent);

	//Child->SetRelativeScale3D({50, 50});
	std::shared_ptr<class URenderBlitz> cube1 = CreateDefaultSubObject<URenderBlitz>();
	RootComponent = cube1;
	cube1->SetRelativeScale3D({1,1,1});
	cube1->SetLocation({20,20,0});

	// Child->SetLocation({});




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

	if (UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}