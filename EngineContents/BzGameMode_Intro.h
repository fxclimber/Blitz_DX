#pragma once
#include <EngineCore/Actor.h>

class ABzGameMode_Intro : public AActor
{
public:
	ABzGameMode_Intro();
	~ABzGameMode_Intro();

	void Tick(float _DeltaTime);

protected:

private:
	std::shared_ptr<class ABzPlayerCube> PlayerCube;
	std::shared_ptr<class ABzBottomTmp> Bottom;
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

};

