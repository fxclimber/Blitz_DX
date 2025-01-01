#include "PreCompile.h"
#include "BlitzPlayerCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "MyRenderer.h"

ABlitzPlayerCube::ABlitzPlayerCube()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// �������� �����.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("Player.png");
	//LogoRenderer->SetTexture("BackGround.png");

	LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	LogoRenderer->SetupAttachment(RootComponent);



	//Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("Player.png", 2);
	//// �θ��� �������� ������ ������ �ָ鼭 ���� 100�� �ƴҼ��� �ִ�
	//Child->SetRelativeLocation({100.0f, 0.0f, 0.0f});
	//Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//Child->SetupAttachment(RootComponent);
}

ABlitzPlayerCube::~ABlitzPlayerCube()
{
}

void ABlitzPlayerCube::BeginPlay()
{
	AActor::BeginPlay();
}

void ABlitzPlayerCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineDebug::OutPutString(Camera->ScreenMousePosToWorldPos().ToString());


	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	FVector Test = GetActorForwardVector();

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	LogoRenderer->AddUVPlusValue({ _DeltaTime, 0.0f, 0.0f, 1.0f });

	if (UEngineInput::IsPress('E'))
	{
		LogoRenderer->ChangeAnimation("Move");
		// �� 1������ ó���Ǵ� �ɷ� 
		// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	}

	if (UEngineInput::IsPress('R'))
	{
		// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}