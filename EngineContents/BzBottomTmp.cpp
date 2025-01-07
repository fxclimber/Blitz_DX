#include "PreCompile.h"
#include "BzBottomTmp.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"


ABzBottomTmp::ABzBottomTmp()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	RendererBottom = CreateDefaultSubObject<UBzRendererDefault>();
	RendererBottom->SetupAttachment(RootComponent);
	RendererBottom->SetMesh("Rect");
	RendererBottom->SetRelativeScale3D({ 45.f,45.f,1.f });
	RendererBottom->SetRotation({ 90.f,0.f,0.f });
}

ABzBottomTmp::~ABzBottomTmp()
{
}

void ABzBottomTmp::BeginPlay()
{
	AActor::BeginPlay();
}

void ABzBottomTmp::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
