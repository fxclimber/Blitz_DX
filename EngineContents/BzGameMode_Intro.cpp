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

#include "ContentsEditorGUI.h"

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("WindowButton"))
		{
			//std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
			//NewMonster->SetActorLocation({ 300.0f, 200.0f, 0.0f });
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("test");

	}
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
	CamInitPos = { 500.0f, 680.0f, -900.0f, 1.0f };
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

	Camera->SetActorLocation(FVector(CamInitPos.X+PlayerCube->GetActorLocation().X, CamInitPos.Y,CamInitPos.Z + PlayerCube->GetActorLocation().Z));

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
	}
	if (UEngineInput::IsPressTime(VK_NUMPAD0))
	{
		//Camera->GetCameraComponent()->SetFOV(50.f);
		ZoomCameraByMoving(Camera.get(), PlayerCube.get(), 30.f);
	}

}
// zoom-in
void ABzGameMode_Intro::ZoomCameraByMoving(ACameraActor* CameraActor, AActor* TargetActor, float ZoomAmount) {
	if (CameraActor && TargetActor) {
		FVector CameraLocation = Camera->GetActorLocation();
		FVector TargetLocation = PlayerCube->GetActorLocation();
		FVector Direction = TargetLocation - CameraLocation;
		Direction.Normalize(); // Direction 벡터가 정규화됨

		FVector NewCameraLocation = CameraLocation + Direction * ZoomAmount;
		CameraActor->SetActorLocation(NewCameraLocation);
	}
}

void ABzGameMode_Intro::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<TestWindow> Window = UEngineGUI::FindGUIWindow<TestWindow>("TestWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
		}

		Window->SetActive(true);
	}

}
