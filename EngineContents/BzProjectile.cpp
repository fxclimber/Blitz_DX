#include "PreCompile.h"
#include "BzProjectile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>

ABzProjectile::ABzProjectile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 100.f,100.f,100.f });
	//Renderer->SetRotation({0.f,90.f,0.f});
	//Renderer->SetWorldLocation({0.f,500.f,0.f});

	SetActorRelativeScale3D({100.f,100.f,100.f});


}

ABzProjectile::~ABzProjectile()
{
}

void ABzProjectile::BeginPlay()
{
}

void ABzProjectile::Tick(float _DeltaTime)
{
}
