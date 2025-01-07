#include "PreCompile.h"
#include "BzEnemyCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>


ABzEnemyCube::ABzEnemyCube()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 20.f,20.f,20.f });
	float yy = Renderer->GetTransformRef().Scale.Y;
	Renderer->SetWorldLocation({ 0.f,yy,0.f });

}

ABzEnemyCube::~ABzEnemyCube()
{
}

void ABzEnemyCube::BeginPlay()
{
	AActor::BeginPlay();
}

void ABzEnemyCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	FVector RotationDelta(0.f, 30.f * _DeltaTime, 0.f); // 초당 100도 회전
	AddActorRotation(RotationDelta);

}
