#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "MyCustomRenderer.h"

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;


	// �κ��丮
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	TimeEventComponent->AddEvent(2.0f,
		[](float _Delta, float _Acc)
		{
			UEngineDebug::OutPutString("Update" + std::to_string(_Acc));
		},
		[]()
		{
			UEngineDebug::OutPutString("Test");
		}, true
	);

	/*TimeEventComponent->AddEndEvent(2.0f, []()
		{
			UEngineDebug::OutPutString("Test");
		}, true
	);*/

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();

	// �������� �����.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetupAttachment(RootComponent);
	LogoRenderer->SetAutoScaleRatio(5.0f);

	LogoRenderer->SetTexture("tevi_n_01.png", true, 5.0f);

	//LogoRenderer->CreateAnimation("Idle", "Tevi", 0, 3, 0.5f);
	//LogoRenderer->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
	//LogoRenderer->ChangeAnimation("Move");
	// LogoRenderer->SetAutoScale(false);

	// �����е鸸�� �������� �ϰ� �ʹٸ� 2���� ����� �ֽ��ϴ�.

	Renderer = CreateDefaultSubObject<MyCustomRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetRelativeScale3D({ 100.0f, 100.0f, 1.0f });

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");
		UEngineFile ImageFiles = Dir.GetFile("BackGround.png");

		// ���� �������̽��� �ȵ˴ϴ�.
		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}

	UColor Color = ColImage.GetColor(FIntPoint{ 3, 3 }, UColor(255, 255, 255, 255));

	int a = 0;

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

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);

	UEngineCore::GetMainWindow().GetMousePos();

	// UEngineDebug::OutPutString(Camera->ScreenMousePosToWorldPos().ToString());


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
		LogoRenderer->AddRelativeLocation({ 0.0f, 0.0f, 1.0f * _DeltaTime });

		// AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		LogoRenderer->AddRelativeLocation({ 0.0f, 0.0f, -1.0f * _DeltaTime });

		// AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	// LogoRenderer->AddUVPlusValue({_DeltaTime, 0.0f, 0.0f, 1.0f});

	if (UEngineInput::IsPress('F'))
	{
		LogoRenderer->ColorData.MulColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	if (UEngineInput::IsPress('E'))
	{
		LogoRenderer->ColorData.PlusColor += float4(1.0f, 1.0f, 1.0f, 1.0f) * _DeltaTime;
		LogoRenderer->ColorData.PlusColor.W += _DeltaTime;

		// LogoRenderer->ChangeAnimation("Move");
		// �� 1������ ó���Ǵ� �ɷ� 
		// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	}

	if (UEngineInput::IsPress('R'))
	{
		LogoRenderer->ColorData.PlusColor -= float4(1.0f, 1.0f, 1.0f, 1.0f) * _DeltaTime;
		LogoRenderer->ColorData.PlusColor.W -= _DeltaTime;

		// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}