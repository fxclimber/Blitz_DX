#pragma once
#include <EngineCore/Actor.h>

class ABlitGameMode_Intro : public AActor
{
public:
	ABlitGameMode_Intro();
	~ABlitGameMode_Intro();

	void Tick(float _DeltaTime);

protected:

private:
	std::shared_ptr<class ABlitzPlayerCube> PlayerCube;
	std::shared_ptr<class ACameraActor> Camera;
};

