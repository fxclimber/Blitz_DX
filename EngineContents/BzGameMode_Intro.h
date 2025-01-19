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

	class ABzPlayerCube* GetPlayer()
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
	class ABzPlayerCube* PlayerCube;
	std::vector < class ABzEnemyCube* > EnemyCubes;
	class ABzEnemyCube* EnemySingleTest;

	class ABzBottom* Bottom;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	UEngineRandom random;

	class ACameraActor* Camera;
	FVector CamInitPos;


};

