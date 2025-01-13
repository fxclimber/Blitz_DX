#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineRandom.h>

class ABzGameMode_Intro : public AGameMode
{
public:
	ABzGameMode_Intro();
	~ABzGameMode_Intro();

	void BeginPlay()override;
	void Tick(float _DeltaTime)override;

	std::shared_ptr<class ABzPlayerCube> GetPlayer()
	{
		return PlayerCube;
	}
	void ZoomCameraByMoving(class ACameraActor* CameraActor, AActor* TargetActor, float ZoomAmount);

	// (imgui에디터에서 선택) 레벨이동한다	
	void LevelChangeStart() override;



protected:
	FVector GetRandomLocation(float _x);
	void SpawnEnemy(FVector randomLocation);

private:
	std::shared_ptr<class ABzPlayerCube> PlayerCube;
	std::vector < std::shared_ptr <class ABzEnemyCube >> EnemyCubes;
	std::shared_ptr<class ABzEnemyCube> EnemySingleTest;

	std::shared_ptr<class ABzBottomTmp> Bottom;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	UEngineRandom random;

	std::shared_ptr<class ABzProjectile> Proj;
	std::shared_ptr<class ACameraActor> Camera;
	FVector CamInitPos;
};

