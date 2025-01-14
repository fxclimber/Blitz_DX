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

class UPlayWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("NAN"))
		{
			//std::shared_ptr<AMonster> NewMonster = GetWorld()->SpawnActor<AMonster>();
			//NewMonster->SetActorLocation({ 300.0f, 200.0f, 0.0f });
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("CAM");
	}
};

ABzGameMode_Intro::ABzGameMode_Intro()
{
    // collision profile name
    GetWorld()->CreateCollisionProfile("Enemy");
    GetWorld()->CreateCollisionProfile("Player");
    GetWorld()->CreateCollisionProfile("Proj");
	// 충돌연결 
    GetWorld()->LinkCollisionProfile("Player","Enemy");
    GetWorld()->LinkCollisionProfile("Proj","Enemy");
    GetWorld()->LinkCollisionProfile("Enemy","Enemy");

	Bottom = GetWorld()->SpawnActor<ABzBottomTmp>();
	Bottom->SetActorRelativeScale3D({ 100.f,100.f ,100.f });
	Bottom->SetActorLocation({0.f,0.f,0.f});


	Camera = GetWorld()->GetMainCamera();
	CamInitPos = { 500.0f, 680.0f, -900.0f, 1.0f };
	Camera->SetActorLocation(CamInitPos);
	Camera->SetActorRotation({ 35.f,340.f,10.f });

	std::shared_ptr<class UEngineCamera> cam = Camera->GetCameraComponent();
	cam->SetProjectionType(EProjectionType::Perspective);

	//-------------
	
}

ABzGameMode_Intro::~ABzGameMode_Intro()
{

}

void ABzGameMode_Intro::BeginPlay()
{
	PlayerCube = std::shared_ptr<ABzPlayerCube>(dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn()));
	PlayerCube->SetActorLocation(FVector{ 200.f,0.f,-500.f });
	PlayerCube->SetActorRotation(FVector{ 0.f,250.f,0.f });

	EnemySingleTest = GetWorld()->SpawnActor<ABzEnemyCube>();
	EnemySingleTest->SetActorLocation({300.f,0.f,600.f});
	//-----
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
	TimeEventComponent->AddEvent(
		.2f,
		[this](float _Delta, float _Acc)
		{
			FVector randomLocation(GetRandomLocation(8.f));
			SpawnEnemy(randomLocation);
		},
		[this]()
		{
		},
		false // 반복 여부
		);
}

void ABzGameMode_Intro::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

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

}


FVector ABzGameMode_Intro::GetRandomLocation(float _x) {
	float range = _x * 100.f;
	float x = this->random.Randomfloat(-range, range);
	float z = this->random.Randomfloat(-range, range);
	float y = this->random.Randomfloat(0.0f, 0.f);
	return FVector(x, y, z);
}

void ABzGameMode_Intro::SpawnEnemy(FVector randomLocation) 
{
	std::shared_ptr<ABzEnemyCube> Enemy = GetWorld()->SpawnActor<ABzEnemyCube>();
	if (Enemy) 
	{
		Enemy->AddRelativeLocation(randomLocation); 
		EnemyCubes.push_back(Enemy); // 배열에 추가
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
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("Editor");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("Editor");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<UPlayWindow> Window = UEngineGUI::FindGUIWindow<UPlayWindow>("Play");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UPlayWindow>("Play");
		}

		Window->SetActive(true);
	}
}


