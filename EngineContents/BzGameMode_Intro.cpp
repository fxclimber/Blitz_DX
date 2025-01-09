#include "PreCompile.h"
#include "BzGameMode_Intro.h"
#include "BzPlayerCube.h"
#include "BzBottomTmp.h"
#include "BzEnemyCube.h"
#include "BzProjectile.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/TimeEventComponent.h>
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
	// 충돌연결 
   // GetWorld()->LinkCollisionProfile("Player","Enemy");
    GetWorld()->LinkCollisionProfile("Proj","Enemy");

	Bottom = GetWorld()->SpawnActor<ABzBottomTmp>();
	Bottom->SetActorRelativeScale3D({ 100.f,100.f ,100.f });
	Bottom->SetActorLocation({0.f,0.f,0.f});
	PlayerCube = GetWorld()->SpawnActor<ABzPlayerCube>();
	PlayerCube->SetActorLocation(FVector{200.f,0.f,-500.f});
	PlayerCube->SetActorRotation(FVector{0.f,250.f,0.f});
	EnemyCube = GetWorld()->SpawnActor<ABzEnemyCube>();

	Camera = GetWorld()->GetMainCamera();
	CamInitPos = { 700.0f, 780.0f, -1000.0f, 1.0f };
	Camera->SetActorLocation(CamInitPos);
	Camera->SetActorRotation({ 35.f,340.f,10.f });

	std::shared_ptr<class UEngineCamera> cam = Camera->GetCameraComponent();
	cam->SetProjectionType(EProjectionType::Perspective);

	//-----
    TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
    TimeEventComponent->AddEvent(
        1.0f,
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
    //UEngineDebug::OutPutString(std::to_string(EnemyCubes.size()));

	//Camera->SetActorLocation(CamInitPos + PlayerCube->GetActorLocation() + FVector(-300.f,100.f,-5000000.f));

	if (UEngineInput::IsDown(VK_LBUTTON))
	{
		FVector PlayerPos = PlayerCube->GetActorLocation();
		FVector offsetPos = {100.f,80.f,0.f};
		FVector PlayerRot = PlayerCube->GetActorTransform().Rotation;
		FVector MoveDir = PlayerCube->GetActorForwardVector();
		float BulletSpeed = 30000.f;
		FVector MoveOffset = (MoveDir * _DeltaTime * BulletSpeed);

		Proj = GetWorld()->SpawnActor<ABzProjectile>();
		Proj->SetPlayer(PlayerCube);
		Proj->SetActorLocation(PlayerCube->GetActorLocation());

		//Proj->SetActorLocation(PlayerPos+ offsetPos);
		//Proj->SetActorRotation(PlayerRot);
		//Proj->AddActorLocation(MoveOffset);


	}

}