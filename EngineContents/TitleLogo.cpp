#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/Renderer.h>

ATitleLogo::ATitleLogo()
{
	// 랜더러를 만든다.
	std::shared_ptr<URenderer> NewRenderer = CreateDefaultSubObject<URenderer>();
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
}