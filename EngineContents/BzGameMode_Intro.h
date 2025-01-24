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

	void LevelChangeStart() override;

	void PathFind();

	std::vector<class ABzEnemyCube*> GetEnemyCubesList()
	{
		return EnemyCubesList;
	}


	class ABzTileMap* map = nullptr;
	class ABzClassManager* Manager;


protected:
	FVector GetRandomLocation(float _x);
	void SpawnEnemy(FVector randomLocation, int _num);

private:
	int Count = 0;
	int MaxCount = 1;
	class ABzPlayerCube* PlayerCube;
	class ABzBottom* Bottom;
	std::vector<class ABzEnemyCube*> EnemyCubesList;

	class UTimeEventComponent* TimeEventComponent;
	UEngineRandom random;


	class ACameraActor* Camera;
	FVector CamInitPos;

	UPathFindAStar PathFinder;
	UEngineRandom Random;
};

