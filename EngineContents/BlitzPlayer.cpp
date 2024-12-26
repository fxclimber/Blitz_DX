#include "PreCompile.h"
#include "BlitzPlayer.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/RenderBlitz.h>
#include <EngineCore/DefaultSceneComponent.h>

ABlitzPlayer::ABlitzPlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	//std::shared_ptr<class URenderBlitz> cube = CreateDefaultSubObject<URenderBlitz>();
	RenderBlitz = CreateDefaultSubObject<URenderBlitz>();
	RenderBlitz->SetupAttachment(RootComponent);
	RenderBlitz->SetRelativeScale3D({ 120.0F, 120.0F, 120.0f });

	Child = CreateDefaultSubObject<USpriteRenderer>();
	Child->SetSprite("Player.png", 2);
	Child->SetRelativeLocation({100.f,0.0f,0.0f});
	Child->SetScale3D({ 50.f,50.f,1.0f });
	Child->SetupAttachment(RootComponent);
}

ABlitzPlayer::~ABlitzPlayer()
{
}

void ABlitzPlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void ABlitzPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress('A'))
	{
		
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

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

}
