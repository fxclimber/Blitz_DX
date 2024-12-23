#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>

ATitleLogo::ATitleLogo()
{
	// 랜더러를 만든다.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("Player.png");


	SetActorRelativeScale3D({ 200.0f, 100.0f, 1.0f });
	SetActorLocation({ 200.0f, 100.0f, 1.0f });
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

	// AddActorLocation(FVector{ 0.001f, 0.0f, 0.0f});
}