#include "PreCompile.h"
#include "BzBottom.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"


ABzBottom::ABzBottom()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	RendererBottom = CreateDefaultSubObject<UBzRendererDefault>();
	RendererBottom->SetupAttachment(RootComponent);
	RendererBottom->SetMesh("cube");
	RendererBottom->SetPivot(PivotType::Bottom);

	//RendererBottom->SetRelativeScale3D({ 1.f,1.f,1.f });
	RendererBottom->GetRenderUnit().SetMaterial("BzDefault");
	RendererBottom->GetRenderUnit().SetTexture("bz_teXture0","b1.jpg");
}

ABzBottom::~ABzBottom()
{
}

void ABzBottom::BeginPlay()
{
	AActor::BeginPlay();
}

void ABzBottom::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
