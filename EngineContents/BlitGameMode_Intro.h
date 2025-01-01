#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ABlitGameMode_Intro : public AActor
{
public:
	// constrcuter destructer
	ABlitGameMode_Intro();
	~ABlitGameMode_Intro();

	void Tick(float _DeltaTime);

protected:

private:
	std::shared_ptr<class ABlitzPlayerCube> PlayerCube;
};

