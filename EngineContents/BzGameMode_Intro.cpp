#include "PreCompile.h"
#include "BzGameMode_Intro.h"
#include "BzPlayerCube.h"
#include "BzBottomTmp.h"
#include "BzEnemyCube.h"
#include "BzProjectile.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/TimeEventComponent.h>
#include <random>
#include <chrono>
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>

class TestWindow : public UEngineGUIWindow
{
public:
	//void OnGUI() override
	//{
	//	ImGui::Button("WindowButton");
	//	ImGui::SameLine(); // 한간 띄기
	//	ImGui::Text("test");

	//}

};

ABzGameMode_Intro::ABzGameMode_Intro()
{
	//UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
	
    // collision profile name
    GetWorld()->CreateCollisionProfile("Enemy");
    GetWorld()->CreateCollisionProfile("Player");
    GetWorld()->CreateCollisionProfile("Proj");

    GetWorld()->LinkCollisionProfile("Player","Enemy");
    GetWorld()->LinkCollisionProfile("Proj","Enemy");

	Bottom = GetWorld()->SpawnActor<ABzBottomTmp>();
	Bottom->SetActorRelativeScale3D({ 100.f,100.f ,100.f });
	Bottom->SetActorLocation({0.f,0.f,0.f});
	PlayerCube = GetWorld()->SpawnActor<ABzPlayerCube>();

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 200.0f, 650.0f, -1000.0f, 1.0f });
	Camera->SetActorRotation({ 35.f,340.f,10.f });

	std::shared_ptr<class UEngineCamera> cam = Camera->GetCameraComponent();
	cam->SetProjectionType(EProjectionType::Perspective);

	//-----
    TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
    TimeEventComponent->AddEvent(
        5.f,
        [this](float _Delta, float _Acc)
        {      
            float randomX = this->random.Randomfloat(-800.0f, 800.0f);
            float randomY = this->random.Randomfloat(0.f, 0.0f);
            float randomZ = this->random.Randomfloat(-800.0f, 800.0f);
            FVector randomLocation(randomX, randomY, randomZ); 

            std::shared_ptr<ABzEnemyCube> Enemy = GetWorld()->SpawnActor<ABzEnemyCube>();
            EnemyCubes.push_back(Enemy);

            if (Enemy) {
                Enemy->AddRelativeLocation(randomLocation); // 상대 위치 추가
            }
        },
        [this]()
        {
        },
        false // 반복 여부
    );
}

ABzGameMode_Intro::~ABzGameMode_Intro()
{

}

void ABzGameMode_Intro::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
    UEngineDebug::OutPutString(std::to_string(EnemyCubes.size()));


	if (UEngineInput::IsPress(VK_LBUTTON))
	{
		FVector PlayerPos = PlayerCube->GetActorLocation();
		FVector offsetPos = {100.f,80.f,0.f};
		FVector PlayerRot = PlayerCube->GetActorTransform().Rotation;
		FVector MoveDir = PlayerCube->GetActorForwardVector();
		float BulletSpeed = 30000.f;
		FVector MoveOffset = (MoveDir * _DeltaTime * BulletSpeed);

		Proj = GetWorld()->SpawnActor<ABzProjectile>();
		Proj->SetPlayer(PlayerCube);

		//Proj->SetActorLocation(PlayerPos+ offsetPos);
		//Proj->SetActorRotation(PlayerRot);
		//Proj->AddActorLocation(MoveOffset);


	}

}