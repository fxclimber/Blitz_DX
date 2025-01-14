#include "PreCompile.h"
#include "CubeTest_Player.h"

#include <EngineCore/Collision.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>

#include "CubeTest_Renderer.h"

ACubeTest_Player::ACubeTest_Player()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<UCubeTest_Renderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetScale3D({ 100.f,100.f,100.f });
	Renderer->SetPivot(CubeTestPivotType::Center);

}

void ACubeTest_Player::BeginPlay()
{
	AActor::BeginPlay();
	SetActorLocation({0.f,100.f,0.f});
}

void ACubeTest_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	FVector rot = { -20.f,30.f,0.f };
	AddActorRotation(rot * _DeltaTime);
}
