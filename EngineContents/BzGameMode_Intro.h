#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineRandom.h>

class ABzGameMode_Intro : public AGameMode
{
public:
	ABzGameMode_Intro();
	~ABzGameMode_Intro();

	void Tick(float _DeltaTime);

	std::shared_ptr<class ABzPlayerCube> GetPlayer()
	{
		return PlayerCube;
	}
	void ZoomCameraByMoving(class ACameraActor* CameraActor, AActor* TargetActor, float ZoomAmount);
		
	void LevelChangeStart() override;



protected:

private:
	std::shared_ptr<class ABzPlayerCube> PlayerCube;
	std::shared_ptr<class ABzEnemyCube> EnemyCube;
	std::shared_ptr<class ABzBottomTmp> Bottom;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	std::vector < std::shared_ptr <class ABzEnemyCube >> EnemyCubes;
	UEngineRandom random;

	std::shared_ptr<class ABzProjectile> Proj;
	std::shared_ptr<class ACameraActor> Camera;
	FVector CamInitPos;
};

