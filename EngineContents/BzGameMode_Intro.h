#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineRandom.h>
#include "PathFindAstar.h"


class ABzGameMode_Intro : public AGameMode
{
public:
	ABzGameMode_Intro();
	~ABzGameMode_Intro();

	void BeginPlay()override;
	void Tick(float _DeltaTime)override;

	class ABzPlayerCube* GetPlayer()
	{
		return PlayerCube;
	}
	void ZoomCameraByMoving(class ACameraActor* CameraActor, AActor* TargetActor, float ZoomAmount);

	// (imgui에디터에서 선택) 레벨이동한다	
	void LevelChangeStart() override;

	//const std::vector<class ABzBottom*>& GetBottomTiles() const
	//{
	//	return BottomTiles;
	//}

	void PathFind();


	//ABzTileMap* GetMap()
	//{
	//	return map;
	//}

	class ABzTileMap* map = nullptr;
	class ABzClassManager* Manager;


protected:
	FVector GetRandomLocation(float _x);
	void SpawnEnemy(FVector randomLocation);
	void UpdateGame();

private:
	class ABzPlayerCube* PlayerCube;
	//std::vector<ABzProjectile*> Bullets;

	std::vector<class ABzEnemyCube*> EnemyCubes;
	class ABzEnemyCube* EnemySingleTest;

	class ABzBottom* Bottom;
	//std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	class UTimeEventComponent* TimeEventComponent;
	UEngineRandom random;

	class ACameraActor* Camera;
	FVector CamInitPos;


	//std::vector<ABzBottom*> BottomTiles;
	//float TileHeight = 0.f;
	//std::vector<float> TileHeights;

	UPathFindAStar PathFinder;
	UEngineRandom Random;
};

