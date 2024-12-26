#include "PreCompile.h"
#include "BlitzPlayer.h"
//#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/RenderBlitz.h>


ABlitzPlayer::ABlitzPlayer()
{
	std::shared_ptr<class URenderBlitz> cube = CreateDefaultSubObject<URenderBlitz>();
	RootComponent = cube;
	cube->SetRelativeScale3D({ 1,1,1.f });
	cube->SetLocation({ 20,20,10 });

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

}
