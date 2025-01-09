#include "PreCompile.h"
#include "Monster2.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "MyCustomRenderer.h"
#include <EngineCore/Collision.h>

AMonster2::AMonster2()
{
	MonsterTypeValue = EMonsterType::Monster2;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 인벤토리
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("Tevi", 0);
	Renderer->SetScale3D({ 50.0f, 50.0f });

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });

}

AMonster2::~AMonster2()
{
}

void AMonster2::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster2::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineCore::GetMainWindow().GetMousePos();

}

// 데이터를 직렬화(압축)
void AMonster2::Serialize(UEngineSerializer& _Ser)
{
	_Ser << GetActorLocation();
}
// 데이터를 복구(할때)
void AMonster2::DeSerialize(UEngineSerializer& _Ser)
{
	FVector Location;
	_Ser >> Location;
	SetActorLocation(Location);
}