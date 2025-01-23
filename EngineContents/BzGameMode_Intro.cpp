#include "PreCompile.h"
#include "BzGameMode_Intro.h"
#include "BzPlayerCube.h"
#include "BzBottom.h"
#include "BzEnemyCube.h"
#include "BzProjectile.h"
#include "BzRendererDefault.h"
#include "BzTileMap.h"
#include "BzClassManager.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineBase/EngineRandom.h>
#include <EngineCore/imgui.h>
#include <EngineCore/TimeEventComponent.h>
#include <EnginePlatform/EngineInput.h>

#include "ContentsEditorGUI.h"
#include <map>
#include <set>

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

		ImGui::SameLine(); // �Ѱ� ���
		ImGui::Text("CAM");
	}
};

ABzGameMode_Intro::ABzGameMode_Intro()
{
	map = GetWorld()->SpawnActor<ABzTileMap>().get();
	PathFinder.SetData(map);

	Manager = GetWorld()->SpawnActor<ABzClassManager>().get();

    // collision profile name
    GetWorld()->CreateCollisionProfile("Enemy");
    GetWorld()->CreateCollisionProfile("Player");
    GetWorld()->CreateCollisionProfile("Proj");
    GetWorld()->CreateCollisionProfile("Skl_BzRockfall");
    GetWorld()->CreateCollisionProfile("Wall");

	// �浹���� 
    GetWorld()->LinkCollisionProfile("Player","Enemy");
    GetWorld()->LinkCollisionProfile("Proj","Enemy");
    GetWorld()->LinkCollisionProfile("Enemy","Enemy");
    GetWorld()->LinkCollisionProfile("Wall","Enemy");
	//----
	Camera = GetWorld()->GetMainCamera().get();
	CamInitPos = { -2000.f,400.f,-4500.f,1.0f };
	CamInitPos += map->MapOffset;
	Camera->SetActorLocation(CamInitPos);
	Camera->SetActorRotation({ 50.f,330.f,0.f });
	Camera->GetCameraComponent()->SetFOV(60.f);

	std::shared_ptr<class UEngineCamera> cam = Camera->GetCameraComponent();
	cam->SetProjectionType(EProjectionType::Perspective);
	//-------------
	
}

ABzGameMode_Intro::~ABzGameMode_Intro()
{

}

void ABzGameMode_Intro::BeginPlay()
{
	AActor::BeginPlay();

	PlayerCube = dynamic_cast<ABzPlayerCube*>(GetWorld()->GetMainPawn());

	FVector PlayerPos = map->MapOffset + FVector::ZERO;
	PlayerCube->SetActorLocation(PlayerPos);
	PlayerCube->SetActorRotation(FVector{ 0.f,290.f,0.f });

	EnemySingleTest = GetWorld()->SpawnActor<ABzEnemyCube>().get();
	FVector EnemySingleTestPos = map->MapOffset + FVector{ 300.f,0.f,600.f };
	EnemySingleTest->SetActorLocation(EnemySingleTestPos);
	//-----
	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>().get();
	TimeEventComponent->AddEvent(
		0.5f,
		[this](float _Delta, float _Acc)
		{
			FVector randomLocation(GetRandomLocation(28.f));
			SpawnEnemy(randomLocation);
		},
		[this]()
		{
		},
		false // �ݺ� ����
		);



}

void ABzGameMode_Intro::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	double fps = 1/ _DeltaTime;
	UEngineDebug::OutPutString("fps: " + std::to_string(fps) );

	Camera->SetActorLocation(FVector(CamInitPos.X+PlayerCube->GetActorLocation().X, CamInitPos.Y,CamInitPos.Z + PlayerCube->GetActorLocation().Z));

	// not tick 
	//PathFind(); 
}


FVector ABzGameMode_Intro::GetRandomLocation(float _x) {
	float range = _x * 100.f;
	float x = this->random.Randomfloat(-range, range);
	float z = this->random.Randomfloat(-range, range);
	float y = this->random.Randomfloat(0.0f, 0.f);
	return FVector(x, y, z) + map->MapOffset;
}

void ABzGameMode_Intro::SpawnEnemy(FVector randomLocation) 
{
	std::shared_ptr<ABzEnemyCube> Enemy = GetWorld()->SpawnActor<ABzEnemyCube>();
	if (Enemy) 
	{
		Enemy->AddRelativeLocation(randomLocation); 
		EnemyCubes.push_back(Enemy.get()); // �迭�� �߰�
	}
}

void ABzGameMode_Intro::UpdateGame()
{
}






// zoom-in
void ABzGameMode_Intro::ZoomCameraByMoving(ACameraActor* CameraActor, AActor* TargetActor, float ZoomAmount) {
	if (CameraActor && TargetActor) {
		FVector CameraLocation = Camera->GetActorLocation();
		FVector TargetLocation = PlayerCube->GetActorLocation();
		FVector Direction = TargetLocation - CameraLocation;
		Direction.Normalize(); // Direction ���Ͱ� ����ȭ��

		FVector NewCameraLocation = CameraLocation + Direction * ZoomAmount;
		CameraActor->SetActorLocation(NewCameraLocation);
	}
}

void ABzGameMode_Intro::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		//std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("Editor");

		//if (nullptr == Window)
		//{
		//	Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("Editor");
		//}

		//Window->SetActive(true);
	}

	{
		//std::shared_ptr<UPlayWindow> Window = UEngineGUI::FindGUIWindow<UPlayWindow>("Play");

		//if (nullptr == Window)
		//{
		//	Window = UEngineGUI::CreateGUIWindow<UPlayWindow>("Play");
		//}

		//Window->SetActive(true);
	}
}

void ABzGameMode_Intro::PathFind()
{
	if (EnemyCubes.empty()) return;

	std::vector<FVector> EnemyTiles;
	float TileScale = map->TileScale;

	FVector PlayerTilePos = FVector(round(PlayerCube->GetActorLocation().X / TileScale) * TileScale,0.f,round(PlayerCube->GetActorLocation().Z / TileScale) * TileScale	);
	UPathFindNode* PlayerNode = map->GetNode(PlayerTilePos);// Ÿ�ϳ�帮�� 
	FVector PlayerNodePos = PlayerNode->pos;

	for (ABzEnemyCube* Enemy : EnemyCubes)
	{
		FVector EnemyTilePos = FVector(round(Enemy->GetActorLocation().X / TileScale) * TileScale,0.f,round(Enemy->GetActorLocation().Z / TileScale) * TileScale);
		UPathFindNode* EnemyNode = map->GetNode(EnemyTilePos);
		if (EnemyNode) EnemyTiles.push_back(EnemyNode->pos);
		//PathFinder.PathFind(EnemyTilePos, PlayerNodePos);
		std::list<FVector> Path = PathFinder.PathFind(EnemyTilePos, PlayerNodePos);
		//int a = 0;

		Enemy->SetPath(Path);
	}



} 

