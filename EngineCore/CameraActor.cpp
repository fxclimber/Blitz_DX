#include "PreCompile.h"
#include "CameraActor.h"
#include "EngineCamera.h"

ACameraActor::ACameraActor()
{
	CameraComponent = CreateDefaultSubObject<UEngineCamera>();
	// 직접 넣어줘야 합니다.
	RootComponent = CameraComponent;
}

ACameraActor::~ACameraActor()
{
	CameraComponent = nullptr;
}

void ACameraActor::BeginPlay()
{
	AActor::BeginPlay();
}

void ACameraActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	CameraComponent->CalculateViewAndProjection();

}

