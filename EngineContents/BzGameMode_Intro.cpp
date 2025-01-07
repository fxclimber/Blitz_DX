#include "PreCompile.h"
#include "BzGameMode_Intro.h"
#include "BzPlayerCube.h"
#include "BzBottomTmp.h"
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
#include "BzEnemyCube.h"

class TestWindow : public UEngineGUIWindow
{
public:
	//void OnGUI() override
	//{
	//	ImGui::Button("WindowButton");
	//	ImGui::SameLine(); // �Ѱ� ���
	//	ImGui::Text("test");

	//}

};

ABzGameMode_Intro::ABzGameMode_Intro()
{
	//UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");

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
    //constexpr int MaxCubes = 10; // �迭 ũ��
    //std::vector<std::shared_ptr<ABzEnemyCube>> EnemyCube;
    int CurrentIndex = 0; // ���� �迭���� ����� �ε���
    //std::shared_ptr<ABzEnemyCube> Enemy = GetWorld()->SpawnActor<ABzEnemyCube>();
    //EnemyCube.push_back(Enemy);


    TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
    TimeEventComponent->AddEvent(
        5.f,
        [this](float _Delta, float _Acc)
        {      
            float randomX = this->random.Randomfloat(-400.0f, 400.0f);
            float randomY = this->random.Randomfloat(-100.0f, 100.0f);
            float randomZ = this->random.Randomfloat(-400.0f, 400.0f);
            FVector randomLocation(randomX, randomY, randomZ); 

            std::shared_ptr<ABzEnemyCube> Enemy = GetWorld()->SpawnActor<ABzEnemyCube>();
            EnemyCubes.push_back(Enemy);

            if (Enemy) {
                Enemy->AddRelativeLocation(randomLocation); // ��� ��ġ �߰�
            }
        },
        [this]()
        {
        },
        false // �ݺ� ����
    );

}

ABzGameMode_Intro::~ABzGameMode_Intro()
{

}

void ABzGameMode_Intro::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);
    UEngineDebug::OutPutString(std::to_string(EnemyCubes.size()));



}