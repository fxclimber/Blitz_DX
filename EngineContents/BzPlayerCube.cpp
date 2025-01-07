#include "PreCompile.h"
#include "BzPlayerCube.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include "BzRendererDefault.h"
#include <EngineCore/TimeEventComponent.h>


ABzPlayerCube::ABzPlayerCube()
{
	// root 역할의 디폴트컴포넌트 
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 여러분들만의 랜더링을 하고 싶다면 2가지 방법이 있습니다.
	Renderer = CreateDefaultSubObject<UBzRendererDefault>();
	Renderer->SetupAttachment(RootComponent);
	//Renderer->SetRelativeScale3D({ 50.0f, 50.0f, 50.0f });
	Renderer->SetScale3D({ 40.f,80.f,20.f });

	float yy = Renderer->GetTransformRef().Scale.Y;
	Renderer->SetWorldLocation({ 0.f,yy,0.f });

#ifdef renderer_test
	//RendererBottom = CreateDefaultSubObject<UBzRendererDefault>();
	//RendererBottom->SetupAttachment(RootComponent);
	//RendererBottom->SetMesh("Rect");
	//RendererBottom->SetRelativeScale3D({ 1500.f,1500.f,1.f });
	//RendererBottom->SetRotation({ 90.f,0.f,0.f });

	// 랜더러를 만든다.
	//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//LogoRenderer->SetupAttachment(RootComponent);
	//LogoRenderer->SetAutoScaleRatio(5.0f);

	//LogoRenderer->CreateAnimation("Idle", "Tevi", 0, 3, 0.5f);
	//LogoRenderer->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
	//LogoRenderer->ChangeAnimation("Move");
	//LogoRenderer->SetAutoScale(false);
#endif renderer_test

	{
		//{// 아틀라스에서 애니 
			//TestSprite->SetSprite("Player.png",2);
			//TestSprite->CreateAnimation("Idle", "Player.png", 0, 70, 0.1f);
			//TestSprite->ChangeAnimation("Idle");
		//}

		{ // 폴더째 스프라이트 애니 
			//TestSprite->CreateAnimation("Move", "Tevi", 4, 16, 0.3f);
			//USpriteRenderer::FrameAnimation* Animation = TestSprite->FindAnimation("Move");
			//Animation->IsAutoScale = true;
			//Animation->AutoScaleRatio = 1.0f;
			//TestSprite->ChangeAnimation("Move");
		}

		{ // 낱장 이미지사용 
			//TestSprite->SetTexture("BackGround.png");
			//TestSprite->SetTexture("Player_Test.png");
		}

	}
	//-------------------------------------
#ifdef TimeEventTest 
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	TimeEventComponent->AddEvent(1.f, // 1초 간격
		[this](float _Delta, float _Acc)
		{
			float yMax = GetActorTransform().Location.Y;

			if (yMax < 400.f) // 아래쪽으로 벗어났을 때
			{
				FVector up(0.f, 250.f * _Delta, 0.f); // 위로 이동
				AddRelativeLocation(up);
			}
			else
			{
				//Destroy(0.0f);
			}
		},
		[this]()
		{
		},
		true // 반복 실행
	);
#endif 
}

ABzPlayerCube::~ABzPlayerCube()
{
}

void ABzPlayerCube::BeginPlay()
{
	AActor::BeginPlay();
}

void ABzPlayerCube::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);



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
		AddRelativeLocation(FVector{ 0.0f, 0.0f, 100.0f * _DeltaTime });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f,0.0f, -100.0f * _DeltaTime });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

}