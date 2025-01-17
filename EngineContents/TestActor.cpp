#include "PreCompile.h"
#include "TestActor.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "MyCustomRenderer.h"
#include <EngineCore/Collision.h>

ATestActor::ATestActor()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
	RootComponent->Parent;

	// 사이드 이펙트.
	std::shared_ptr<URenderer> Renderer = CreateDefaultSubObject<URenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->CreateRenderUnit();
	Renderer->Parent;

	URenderUnit& Unit = Renderer->GetRenderUnit();
	Unit.SetMesh("Test");
	Unit.SetMaterial("Test");


	// Renderer->SetTexture("Test.png");
	// Renderer->SetScale3D({ 50.0f, 50.0f });

}

ATestActor::~ATestActor()
{
}

void ATestActor::BeginPlay()
{
	AActor::BeginPlay();
}

void ATestActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AddActorRotation({0.0f, 0.0f, 360.0f * _DeltaTime });
}	
